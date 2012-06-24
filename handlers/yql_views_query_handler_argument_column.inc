<?php
class yql_views_query_handler_argument_column extends yql_views_query_handler_argument {
  function init(&$view, $options) {
    parent::init($view, $options);
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['case'] = array('default' => 'none');
    $options['path_case'] = array('default' => 'none');
    $options['transform_dash'] = array('default' => FALSE);
    $options['field_name'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['case'] = array(
      '#type' => 'select',
      '#title' => t('Case'),
      '#description' => t('When printing the argument result, how to transform the case.'),
      '#options' => array(
        'none' => t('No transform'),
        'upper' => t('Upper case'),
        'lower' => t('Lower case'),
        'ucfirst' => t('Capitalize first letter'),
        'ucwords' => t('Capitalize each word'),
      ),
      '#default_value' => $this->options['case'],
    );

    $form['path_case'] = array(
      '#type' => 'select',
      '#title' => t('Case in path'),
      '#description' => t('When printing url paths, how to transform the case of the argument. Do not use this unless with Postgres as it uses case sensitive comparisons.'),
      '#options' => array(
        'none' => t('No transform'),
        'upper' => t('Upper case'),
        'lower' => t('Lower case'),
        'ucfirst' => t('Capitalize first letter'),
        'ucwords' => t('Capitalize each word'),
      ),
      '#default_value' => $this->options['path_case'],
    );

    $form['transform_dash'] = array(
      '#type' => 'checkbox',
      '#title' => t('Transform spaces to dashes in URL'),
      '#default_value' => $this->options['transform_dash'],
    );

    $form['field_name'] = array(
      '#title' => t('Field name'),
      '#description' => t('The field name that will receive this argument. Example: Rating.AverageRating'),
      '#type' => 'textfield',
      '#default_value' => $this->options['field_name'],
      '#required' => TRUE,
    );

  }

  /**
   * Build the summary query based on a string
   */
  function summary_query() {
    $this->base_alias = $this->name_alias = $this->query->add_field($this->table_alias, $this->real_field);
    $this->query->set_count_field($this->table_alias, $this->real_field);

    return $this->summary_basics(FALSE);
  }

  /**
   * Build the query based upon the formula
   */
  function query() {
    $argument = $this->argument;
    if (!empty($this->options['transform_dash'])) {
      $argument = strtr($argument, '-', ' ');
    }

    $field = $this->options['field_name'];
    $this->query->add_where(0, "$field = '$argument'", $field, $argument);
  }

  function summary_argument($data) {
    $value = $this->case_transform($data->{$this->base_alias}, 'path_case');
    if (!empty($this->options['transform_dash'])) {
      $value = strtr($value, ' ', '-');
    }

    return $value;
  }

  function case_transform($string, $option) {
    global $multibyte;

    switch ($this->options[$option]) {
      default:
        return $string;
      case 'upper':
        return drupal_strtoupper($string);
      case 'lower':
        return drupal_strtolower($string);
      case 'ucfirst':
        return drupal_strtoupper(drupal_substr($string, 0, 1)) . drupal_substr($string, 1);
      case 'ucwords':
        if ($multibyte == UNICODE_MULTIBYTE) {
          return mb_convert_case($string, MB_CASE_TITLE);
        }
        else {
          return ucwords($string);
        }
    }
  }

  function title() {
    $title = $this->case_transform($this->argument, 'case');
    if (!empty($this->options['transform_dash'])) {
      $title = strtr($title, '-', ' ');
    }

    return check_plain($title);
  }

  function summary_name($data) {
    return $this->case_transform(parent::summary_name($data), 'case');
  }
}
