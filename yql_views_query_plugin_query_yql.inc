<?php

class yql_views_query_plugin_query_yql extends views_plugin_query {

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table = 'yql_ep', $base_field, $options) {
    parent::init($base_table, $base_field, $options);

    $this->api_url = !empty($this->options['api_url']) ? $this->options['api_url'] : 'http://query.yahooapis.com/v1/public/yql';
    $this->api_method = $this->options['api_method'] ? $this->options['api_method'] : 'json';
    $this->yql_base_table = $this->options['yql_base_table'];
  }

  /**
   * Construct the "WHERE" or "HAVING" part of the query.
   *
   * @param $where
   *   'where' or 'having'.
   */
  function condition_query($where = 'where') {
    $clauses = array();
    foreach ($this->$where as $group => $info) {
      if (empty($info['clauses'])) {
        continue;
      }
      $clause = implode(") " . $info['type'] . " (", $info['clauses']);
      if (count($info['clauses']) > 1) {
        $clause = '(' . $clause . ')';
      }
      $clauses[] = $clause;
    }

    if ($clauses) {
      $keyword = drupal_strtoupper($where);
      if (count($clauses) > 1) {
        return "$keyword (" . implode(")\n    " . $this->group_operator . ' (', array_filter($clauses)) . ")\n";
      }
      else {
        return "$keyword " . array_shift($clauses) . "\n";
      }
    }
    return "";
  }

  function use_pager() {
    return FALSE;
  }

  /**
   * Generate a query and a countquery from all of the information supplied
   * to the object.
   *
   * @param $get_count
   *   Provide a countquery if this is true, otherwise provide a normal query.
   */
  function query($view, $get_count = FALSE) {
    $query = '';

    // Add the where clauses
    $where = ' ' . $this->condition_query();

    // Add the field clauses
    $fields = '';
    $fields_array = $this->fields;
    foreach ($fields_array as $alias => $field) {
      if (!empty($fields)) {
        $fields .= ', ';
      }
      $fields .= $field['field'];
    }
    // Add the base table
    $from = $this->yql_base_table;

    // Add sort function
    if (isset($this->orderby) && $this->orderby) {
      // Only get the first orderby
      $orderby_field = current($this->orderby);
      $orderby = " | sort(field=\"" . $orderby_field['field'] . "\")";

      switch ($orderby_field['order']) {
        case 'ASC':
        case 'asc':
          // Do nothing. This is added only for clarity.
          break;

        case 'DESC':
        case 'desc':
          $orderby = $orderby . ' | reverse()';
          break;

        default:
          break;
      }
    }

    // Build the query string
    $query = "SELECT $fields FROM $from";
    if (!empty($where)) {
      $query = "$query $where";
    }
    // Add table definitions
    if (!empty($this->options['yql_custom_tables'])) {
      $query = $this->options['yql_custom_tables'] . $query;
    }

    // Add sort definitions
    if (!empty($orderby)) {
      $query = $query . $orderby;
    }
    return $query;
  }


  /**
   * Get the arguments attached to the WHERE and HAVING clauses of this query.
   */
  function get_where_args() {
    $args = array();
    foreach ($this->where as $group => $where) {
      $args = array_merge($args, $where['args']);
    }

    if (isset($this->having) && $this->having) {
      foreach ($this->having as $group => $having) {
        $args = array_merge($args, $having['args']);
      }
    }
    return $args;
  }

  function add_param($param, $value = '') {
    $this->params[$param] = $value;
  }

  function add_where($group, $clause) {
    $args = func_get_args();
    array_shift($args); // ditch $group
    array_shift($args); // ditch $clause

    // Expand an array of args if it came in.
    if (count($args) == 1 && is_array(reset($args))) {
      $args = current($args);
    }

    // Ensure all variants of 0 are actually 0. Thus '', 0 and NULL are all
    // the default group.
    if (empty($group)) {
      $group = 0;
    }

    // Check for a group.
    if (!isset($this->where[$group])) {
      $this->set_where_group('AND', $group);
    }

    // Add the clause and the args.
    if (is_array($args)) {
      $this->where[$group]['clauses'][] = $clause;
      // we use array_values() here to prevent array_merge errors as keys from multiple
      // sources occasionally collide.
      $this->where[$group]['args'] = array_merge($this->where[$group]['args'], array_values($args));
    }
  }

  /**
   * Let modules modify the query just prior to finalizing it.
   */
  function alter(&$view) {
    foreach (module_implements('yql_views_query_query_alter') as $module) {
      $function = $module . '_yql_views_query_query_alter';
      $function($view, $this);
    }
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->init_pager($view);

    // Let the pager modify the query to add limits.
    $this->pager->query();

    $view->build_info['query'] = $this->query($view);
    //$view->build_info['count_query'] = $this->query($view, TRUE);
    $view->build_info['count_query'] = '';
    $view->build_info['query_args'] = $this->get_where_args();
  }

  /**
   * Alter the query for paging settings. This should only be called
   * if the view is using pager.
   * @param $query
   *   The query to be altered
   * @param $limit
   *   The number of items limit
   * @param $offset
   *   The offset from the first item
   */
  function _query_alter_limit(&$query, $limit, $offset) {
    $base_table = $this->options['yql_base_table'];
    // $total_aggregate_items = $offset + $limit;

    // @todo if there is a better way, fix this!
    $total_aggregate_items = $this->options['num_items'];

    $query = str_replace('FROM ' . $base_table, 'FROM ' . $base_table . '(0,' . $total_aggregate_items . ')', $query);

    /*
     // If sort function is specified, the limit and offset should be put
     // before the sort function
     if ($sort_found = strpos($query, '|')) {
     $query = substr($query, 0, $sort_found -1) . "limit $limit offset $offset " . substr($query, $sort_found);
     }
     else {
     $query .= " limit $limit offset $offset";
     }
     */

    $current_tail = $offset + $limit;
    $query = $query . " | truncate(count=$current_tail) | tail(count=$limit)";
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   */
  function execute(&$view) {
    $query = $view->build_info['query'];
    $args = $view->build_info['query_args'];

    if ($query) {
      // Initialize, alter and set the pager settings before executing
      if ($this->pager->use_pager()) {
        $this->pager->total_items = $this->options['num_items'];
        $view->total_rows = $this->options['num_items'];

        if (!empty($this->pager->options['offset'])) {
          $this->pager->total_items -= $this->pager->options['offset'];
        }
        $this->pager->update_page_info();
      }

      // We can't have an offset without a limit, so provide an upperbound limit instead.
      $limit  = intval(!empty($this->limit) ? $this->limit : $this->options['num_items']);
      $offset = intval(!empty($this->offset) ? $this->offset : 0);
      $this->_query_alter_limit($query, $limit, $offset);

      // Let the pager modify the query to add limits.
      $this->pager->pre_execute($query, $args);

      $replacements = module_invoke_all('views_query_substitutions', $view);
      $query = str_replace(array_keys($replacements), $replacements, $query);

      // Encode the query into URL friendly format
      $query = urlencode($query);
      $format_string = $this->api_method == 'json' ? '&format=json' : '&format=xml';
      $url = $this->api_url . '?q=' . $query . $format_string;

      $start = $this->float_microtime();

      $results = drupal_http_request($url, array('headers' => array()));

      // There is an error in the HTTP request
      if (isset($results->error)) {
        // If the error comes from YQL query, print the YQL error details.
        if (isset($results->data)) {
          $yql_error = json_decode($results->data, TRUE);
          drupal_set_message("YQL query error: " . $yql_error['error']['description'], 'error');
        }
        // Otherwise, the error comes from HTTP request error.
        else {
          drupal_set_message("HTTP request error: " . $results->error, 'error');
        }
        return;
      }

      switch ($this->api_method) {
        case 'xml':
          // Not supported yet.
          return;
        case 'json':
        default:
          $results = json_decode($results->data, TRUE);
          break;
      }

      if ($results['query']['results']) {
        // If the base object is specified, use that. Otherwise use the first object.
        if (!empty($this->options['yql_base_object']) && isset($results['query']['results'][$this->options['yql_base_object']])) {
          $result_array = $results['query']['results'][$this->options['yql_base_object']];
        }
        else {
          $result_array = current($results['query']['results']);
        }

        $view->result = $result_array;

        foreach ($view->result as $key => $value) {
          $view->result[$key] = (object) $value;
        }

        // Save the metadata into the object
        unset($results['query']['results']);
        foreach ($results as $key => $value) {
          $this->$key = $value;
        }
      }
      $this->pager->post_execute($view->result);
    }
    //dpm($url);
    $view->execute_time = $this->float_microtime() - $start;
  }

  function float_microtime() {
    list($usec, $sec) = explode(' ', microtime());
    return (float) $sec + (float) $usec;
  }
  
  function add_signature(&$view) {
    //$view->query->add_field(NULL, "'" . $view->name . ':' . $view->current_display . "'", 'view_name');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['api_url'] = array('default' => 'http://query.yahooapis.com/v1/public/yql');
    $options['api_method'] = array('default' => 'json');
    $options['yql_base_table'] = array('default' => '');
    $options['yql_custom_table'] = array('default' => '');
    $options['yql_base_object'] = array('default' => '');

    $options['num_items'] = array('default' => 10);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['api_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternate API URL'),
      '#default_value' => $this->options['api_url'],
      '#description' => t("The URL YQL will be queried from (default: Yahoo! YQL Engine)."),
    );

    $form['api_method'] = array(
      '#type' => 'select',
      '#title' => t('API method'),
      '#description' => t("The format of the data returned by YQL."),
      '#default_value' => 'json',
      '#options' => array(
        'json' => 'JSON',
      ),
      '#required' => TRUE,
    );

    $form['yql_base_table'] = array(
      '#type' => 'textfield',
      '#title' => t('YQL base table'),
      '#default_value' => $this->options['yql_base_table'],
      '#description' => t("A base table that view will be querying by using YQL to. Example: flickr.photos.recent"),
      '#required' => TRUE,
    );

    $form['num_items'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of items'),
      '#required' => TRUE,
      '#description' => t('The number of items to be fetched from the base table. The number must be lesser than the remote limit of the base table, To get the remote limit of a table, see: ') . l('YQL Guide: Paging', 'http://developer.yahoo.com/yql/guide/paging.html') . '. NOTE: This amount of item will be fetched on every page of the view, so it might affect the performance of your site',
      '#default_value' => $this->options['num_items'],
    );

    // @todo: add validation for custom open table.
    $form['yql_custom_tables'] = array(
      '#type' => 'textarea',
      '#title' => t('Custom open tables.'),
      '#default_value' => $this->options['yql_custom_tables'],
      '#description' => t("Add custom table into the YQL Query.<br/>Example:" . 'USE \'http://www.datatables.org/delicious/delicious.feeds.popular.xml\' AS delicious.feeds.popular;'),
    );

    $form['yql_base_object'] = array(
      '#type' => 'textfield',
      '#title' => t('YQL base object'),
      '#default_value' => $this->options['yql_base_object'],
      '#description' => t('The base object YQL will be querying from. If this is left empty, the first object in the result set will be taken as the base object'),
    );
  }

  /**
   * Add a field to the query table, possibly with an alias. This will
   * automatically call ensure_table to make sure the required table
   * exists, *unless* $table is unset.
   *
   * @param $table
   *   The table this field is attached to. If NULL, it is assumed this will
   *   be a formula; otherwise, ensure_table is used to make sure the
   *   table exists.
   * @param $field
   *   The name of the field to add. This may be a real field or a formula.
   * @param $alias
   *   The alias to create. If not specified, the alias will be $table_$field
   *   unless $table is NULL. When adding formulae, it is recommended that an
   *   alias be used.
   * @param $params
   *   An array of parameters additional to the field that will control items
   *   such as aggregation functions and DISTINCT.
   *
   * @return $name
   *   The name that this field can be referred to as. Usually this is the alias.
   */
  function add_field($table, $field, $alias = '', $params = array()) {
    // We can't use any alias in YQL query, so just use the real field name.
    $alias = $field;

    // Create a field info array.
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $alias,
    ) + $params;

    if (empty($this->fields[$alias])) {
      $this->fields[$alias] = $field_info;
    }

    return $alias;
  }

  /**
   * Add an ORDER BY clause to the query.
   *
   * @param $table
   *   The table this field is part of. If a formula, enter NULL.
   * @param $field
   *   The field or formula to sort on. If already a field, enter NULL
   *   and put in the alias.
   * @param $order
   *   Either ASC or DESC.
   * @param $alias
   *   The alias to add the field as. In SQL, all fields in the order by
   *   must also be in the SELECT portion. If an $alias isn't specified
   *   one will be generated for from the $field; however, if the
   *   $field is a formula, this alias will likely fail.
   * @param $params
   *   Any params that should be passed through to the add_field.
   */
  function add_orderby($table, $field, $order, $alias = '', $params = array()) {
    // We can't use any alias in YQL query, so just use the real field name.
    $as = $alias = $field;

    if ($field) {
      $as = $this->add_field($table, $field, $as, $params);
    }

    $orderby = array(
      'field' => $as,
      'order' => $order,
    );

    $this->orderby[] = $orderby;
  }


}
