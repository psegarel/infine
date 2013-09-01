<?php
/**
 * @file
 * infine_custom_menus.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function infine_custom_menus_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-social.
  $menus['menu-social'] = array(
    'menu_name' => 'menu-social',
    'title' => 'Social',
    'description' => 'Social links menu - Facebook, Twitter, etc.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Social');
  t('Social links menu - Facebook, Twitter, etc.');


  return $menus;
}
