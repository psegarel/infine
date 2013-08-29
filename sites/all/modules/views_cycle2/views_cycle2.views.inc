<?php

require_once 'views_cycle2_plugin_style_cycle.inc';

/**
 * Implements hook_views_plugins
 * @return array
 */
function views_cycle2_views_plugins() {
  return array(
    'module' => 'views_cycle2',
    'style' => array(
      'views_cycle2' => array(
        'title' => t('Views Cycle2 slideshow'),
        'help' => t('Responsive slideshow with Cycle2 plugin'),
        'handler' => 'views_cycle2_plugin_style_cycle',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'uses row class' => TRUE,
        'type' => 'normal',
        'parent' => 'list',
        'path' => drupal_get_path('module', 'views_cycle2'),
        'theme' => 'views_cycle2',
        'theme path' => drupal_get_path('module', 'views_cycle2'),
      ),
    )
  );
}