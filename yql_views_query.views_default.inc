<?php
/**
 * Implements hook_views_default_views().
 */
function yql_views_query_views_default_views() {
  /*
   * View 'yql_flickr_photos_recent'
   */
  $view = new view;
  $view->name = 'yql_flickr_photos_recent';
  $view->description = 'YQL Example: List out the latest photos from Flickr with YQL';
  $view->tag = 'YQL demo';
  $view->view_php = '';
  $view->base_table = 'yql';
  $view->is_cacheable = FALSE;
  $view->api_version = '3.0-alpha1';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Example YQL Views Page: Flickr Recent Photos';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['api_url'] = '';
  $handler->display->display_options['query']['options']['yql_base_table'] = 'flickr.photos.recent';
  $handler->display->display_options['query']['options']['num_items'] = '10';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'column' => 'column',
    'column_2' => 'column_2',
    'column_1' => 'column_1',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'column' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_2' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_1' => array(
      'align' => '',
      'separator' => '',
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column']['id'] = 'column';
  $handler->display->display_options['fields']['column']['table'] = 'yql';
  $handler->display->display_options['fields']['column']['field'] = 'column';
  $handler->display->display_options['fields']['column']['label'] = 'title';
  $handler->display->display_options['fields']['column']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column']['field_name'] = 'title';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_2']['id'] = 'column_2';
  $handler->display->display_options['fields']['column_2']['table'] = 'yql';
  $handler->display->display_options['fields']['column_2']['field'] = 'column';
  $handler->display->display_options['fields']['column_2']['label'] = 'owner';
  $handler->display->display_options['fields']['column_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_2']['field_name'] = 'owner';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_1']['id'] = 'column_1';
  $handler->display->display_options['fields']['column_1']['table'] = 'yql';
  $handler->display->display_options['fields']['column_1']['field'] = 'column';
  $handler->display->display_options['fields']['column_1']['label'] = 'id';
  $handler->display->display_options['fields']['column_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_1']['field_name'] = 'id';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'See in Flickr';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Link';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'http://flickr.com/photos/[column_2]/[column_1]/';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'yql_flickr_photos_recent';
  $views[$view->name] = $view;

  /*
   * View 'yql_sushi'
   */
  $view = new view;
  $view->name = 'yql_sushi';
  $view->description = 'YQL Example: List Out Sushi Restaurant in a Particular Location';
  $view->tag = 'YQL demo';
  $view->view_php = '';
  $view->base_table = 'yql';
  $view->is_cacheable = FALSE;
  $view->api_version = '3.0-alpha1';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Example YQL Views Page: \'Sushi\' Restaurant';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['api_url'] = '';
  $handler->display->display_options['query']['options']['yql_base_table'] = 'local.search';
  $handler->display->display_options['query']['options']['num_items'] = '30';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'column' => 'column',
    'column_1' => 'column_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'column' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_1' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column']['id'] = 'column';
  $handler->display->display_options['fields']['column']['table'] = 'yql';
  $handler->display->display_options['fields']['column']['field'] = 'column';
  $handler->display->display_options['fields']['column']['label'] = 'Title';
  $handler->display->display_options['fields']['column']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column']['field_name'] = 'Title';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_2']['id'] = 'column_2';
  $handler->display->display_options['fields']['column_2']['table'] = 'yql';
  $handler->display->display_options['fields']['column_2']['field'] = 'column';
  $handler->display->display_options['fields']['column_2']['label'] = 'Address';
  $handler->display->display_options['fields']['column_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_2']['field_name'] = 'Address';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_1']['id'] = 'column_1';
  $handler->display->display_options['fields']['column_1']['table'] = 'yql';
  $handler->display->display_options['fields']['column_1']['field'] = 'column';
  $handler->display->display_options['fields']['column_1']['label'] = 'Rating.AverageRating';
  $handler->display->display_options['fields']['column_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_1']['field_name'] = 'Rating.AverageRating';
  /* Sort criterion: YQL: Column */
  $handler->display->display_options['sorts']['column']['id'] = 'column';
  $handler->display->display_options['sorts']['column']['table'] = 'yql';
  $handler->display->display_options['sorts']['column']['field'] = 'column';
  $handler->display->display_options['sorts']['column']['order'] = 'DESC';
  $handler->display->display_options['sorts']['column']['field_name'] = 'Rating.AverageRating';
  /* Filter: YQL: Column */
  $handler->display->display_options['filters']['column']['id'] = 'column';
  $handler->display->display_options['filters']['column']['table'] = 'yql';
  $handler->display->display_options['filters']['column']['field'] = 'column';
  $handler->display->display_options['filters']['column']['value'] = 'sushi';
  $handler->display->display_options['filters']['column']['case'] = 1;
  $handler->display->display_options['filters']['column']['field_name'] = 'query';
  /* Filter: YQL: Column */
  $handler->display->display_options['filters']['column_1']['id'] = 'column_1';
  $handler->display->display_options['filters']['column_1']['table'] = 'yql';
  $handler->display->display_options['filters']['column_1']['field'] = 'column';
  $handler->display->display_options['filters']['column_1']['value'] = 'san fransisco, ca';
  $handler->display->display_options['filters']['column_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['column_1']['expose']['operator'] = 'column_1_op';
  $handler->display->display_options['filters']['column_1']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['column_1']['expose']['use_operator'] = 0;
  $handler->display->display_options['filters']['column_1']['expose']['identifier'] = 'column_1';
  $handler->display->display_options['filters']['column_1']['case'] = 1;
  $handler->display->display_options['filters']['column_1']['field_name'] = 'location';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'yql_sushi';
  $views[$view->name] = $view;

  return $views;
}
