<?php
/**
 * @file
 * infine_custom_menus.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function infine_custom_menus_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-social:http://facebook.com
  $menu_links['menu-social:http://facebook.com'] = array(
    'menu_name' => 'menu-social',
    'link_path' => 'http://facebook.com',
    'router_path' => '',
    'link_title' => 'Facebook',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'social-icon-facebook',
          1 => 'social-icon',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: menu-social:http://twitter.com
  $menu_links['menu-social:http://twitter.com'] = array(
    'menu_name' => 'menu-social',
    'link_path' => 'http://twitter.com',
    'router_path' => '',
    'link_title' => 'Twitter',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'social-icon-twitter',
          1 => 'social-icon',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: menu-social:http://youtube.com
  $menu_links['menu-social:http://youtube.com'] = array(
    'menu_name' => 'menu-social',
    'link_path' => 'http://youtube.com',
    'router_path' => '',
    'link_title' => 'Youtube',
    'options' => array(
      'attributes' => array(
        'class' => array(
          0 => 'social-icon-youtube',
          1 => 'social-icon',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Facebook');
  t('Twitter');
  t('Youtube');


  return $menu_links;
}
