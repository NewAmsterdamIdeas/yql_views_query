<?php
class yql_views_query_handler_sort_column extends yql_views_query_handler_sort {
  function option_definition() {
    $options = parent::option_definition();

    $options['field_name'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['field_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Field name'),
      '#description' => t('The field name that the sorting will be done from. NOTE: Only the first field name in the sort handler that will be taken for sorting.'),
      '#default_value' => $this->options['field_name'],
      '#required' => TRUE,
    );
  }

  /**
   * Called to add the sort to a query.
   */
  function query() {
    $this->query->add_orderby($this->table_alias, $this->options['field_name'], $this->options['order']);
  }

  /**
   * Display whether or not the sort order is ascending or descending
   */
  function admin_summary() {
    $field = $this->options['field_name'];

    if (!empty($this->options['exposed'])) {
      return $field . ' ' . t('Exposed');
    }
    switch ($this->options['order']) {
      case 'ASC':
      case 'asc':
      default:
        return $field . ' ' . t('asc');
        break;
      case 'DESC':
      case 'desc':
        return $field . ' ' . t('desc');
        break;
    }
  }
}
