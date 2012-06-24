<?php
class yql_views_query_handler_argument extends views_handler_argument {
  /**
   * Get the argument's label
   */
  function field_name() {
    if (!isset($this->options['field_name'])) {
      return '';
    }
    return $this->options['field_name'];
  }

  function admin_summary() {
    return $this->field_name();
  }
}
