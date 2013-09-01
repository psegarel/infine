<?php
/**
 * @file
 * infine_type_sponsors.features.inc
 */

/**
 * Implements hook_node_info().
 */
function infine_type_sponsors_node_info() {
  $items = array(
    'sponsors' => array(
      'name' => t('Sponsor'),
      'base' => 'node_content',
      'description' => t('Sponsors of the event - represented by image'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
