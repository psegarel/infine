<?php

require_once 'node.preprocessor.inc';

function infine_preprocess_page(&$variables) {
  drupal_add_css("http://fonts.googleapis.com/css?family=Open+Sans:400italic,700italic,400,300,700", 'external');

  drupal_add_css(drupal_get_path('theme', 'infine') . '/icons/pictopro-normal/pictopro-normal.css');
  drupal_add_css(drupal_get_path('theme', 'infine') . '/icons/pictopro-outline/pictopro-outline.css');
}

/**
 * Implements hook_preprocess_node()
 * @param $variables
 */
function infine_preprocess_node(&$variables) {
  $node = $variables['node'];


  // @example: node--features--teaser.tpl.php
  $variables['theme_hook_suggestions'][] = 'node__' . $node->type . '__' . $variables['view_mode'];
  foreach($variables['classes_array'] as $id => $class) {

    if($class == 'row-fluid') {
      unset($variables['classes_array'][$id]);
    }
  }

  if(isset($node->class)) {
    $variables['classes_array'][] = $node->class['class'];
  }



  if($node->type == 'session') {
    _infine_wrap_field('field_presenter', $variables['content'], array('class' => array('name')));
    _infine_wrap_field('field_presenters_title', $variables['content'], array('class' => array('company')));
    _infine_wrap_field('field_session_time', $variables['content'], array('class' => array('time')));

    _infine_group_fields(array('field_about_title', 'field_about_description'), 'about', $variables['content'], array('class' => array('about')));
  }
}