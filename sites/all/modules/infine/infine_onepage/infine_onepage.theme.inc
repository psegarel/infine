<?php

/**
 * Implements hook_theme()
 * @return array
 */
function infine_onepage_theme() {
  return array(
    'infine_onepage_form_table' => array(
      'render element' => 'form'
    ),
    'infine_onepage_page' => array(
      'arguments' => array('page'),
      'template' => 'template/infine-onepage-page',
    ),

    'infine_onepage' => array(
      'arguments' => array('page', 'add_form'),
      'template' => 'template/infine-onepage',
    ),
    'infine_onepage_container' => array(
      'arguments' => array('container', 'add_form'),
      'template' => 'template/infine-onepage-container',
    ),
    'infine_onepage_row' => array(
      'arguments' => array('row', 'add_form'),
      'template' => 'template/infine-onepage-row',
    ),
    'infine_onepage_component' => array(
      'arguments' => array('component'),
      'template' => 'template/infine-onepage-component',
    ),
  );
}

/**
 * @param $variables
 */
function template_preprocess_infine_onepage(&$variables) {
  drupal_add_js(drupal_get_path('module', 'infine_onepage') . '/js/infine_onepage.js');
  drupal_add_library('system', 'ui.sortable');

  drupal_add_css(drupal_get_path('module', 'infine_onepage') . '/css/bootstrap.css');
  drupal_add_css(drupal_get_path('module', 'infine_onepage') . '/css/infine-onepage.css');

  $page = $variables['page'];
  $ids = _infine_onepage_get_ids($page, 'page');

  $containers = infine_onepage_get_containers($page->id);
  foreach ($containers as $container) {
    $add_form = drupal_get_form('infine_onepage_form_row', $container);

    $variables['containers'][] = theme(
      'infine_onepage_container',
      array('container' => $container, 'add_form' => $add_form)
    );
  }

  $variables['element_attributes'] = unserialize($page->attributes);
  $variables['add_form'] = drupal_render($variables['add_form']);
  $variables['page_id'] = $ids['wrapper_id'];
}

/**
 * @param $variables
 */
function template_preprocess_infine_onepage_container(&$variables) {
  $container = $variables['container'];
  $ids = _infine_onepage_get_ids($container, 'container');

  $page = infine_onepage_page_load($container->page_id);
  $rows = infine_onepage_get_rows($container->id);
  $variables['rows'] = array();

  foreach ($rows as $row) {
    $add_form = drupal_get_form('infine_onepage_form_component', $row);
    $variables['rows'][] = theme('infine_onepage_row', array('row' => $row, 'add_form' => $add_form));
  }

  $variables['element_attributes'] = $container->attributes;
  $variables['container_class'] = !empty($container->fullwidth) ? 'container-fullwidth' : 'container';
  $variables['container_form'] = drupal_get_form('infine_onepage_form_container', $page, $container);

  $variables['add_form'] = drupal_render($variables['add_form']);
  $variables['form_id'] = $ids['form_id'];
  $variables['container_id'] = $ids['wrapper_id'];
}

/**
 * @param $variables
 */
function template_process_infine_onepage_row(&$variables) {
  $row = $variables['row'];
  $ids = _infine_onepage_get_ids($row, 'row');
  $container = infine_onepage_container_load($row->container_id);

  $components = infine_onepage_get_components($row->id);

  $variables['components'] = array();
  $variables['components_forms'] = array();

  foreach($components as $component) {
    $variables['components'][] = theme('infine_onepage_component', array('component' => $component));
    $variables['component_forms'][] = drupal_get_form('infine_onepage_form_component', $row, $component);
  }


  if(!is_array($row->attributes)) {
    $variables['element_attributes'] = unserialize($row->attributes);
  } else {
    $variables['element_attributes'] = $row->attributes;
  }

  $variables['add_form'] = drupal_render($variables['add_form']);
  $variables['row_id'] = $ids['wrapper_id'];

  $variables['row_class'] = 'row';
  if($container->fullwidth) {
    $variables['row_class'] = 'row-fullwidth';
  }

  $variables['span_class'] = 'span12';
  if($container->fullwidth) {
    $variables['span_class'] = 'span-fullwidth';
  }

}

/**
 * @param $variables
 */
function template_process_infine_onepage_component(&$variables) {
  $component = $variables['component'];
  $ids = _infine_onepage_get_ids($component, 'component');

  if(!is_array($component->attributes)) {
    $variables['element_attributes'] = unserialize($component->attributes);
  } else {
    $variables['element_attributes'] = $component->attributes;
  }

  $variables['element_attributes']['class'][] = 'component';
  $variables['element_attributes']['id'] = $ids['wrapper_id'];

  $variables['form_id'] = $ids['form_id'];
}


function template_preprocess_infine_onepage_page(&$variables) {
  $page_id = $variables['page'];

  $containers = infine_onepage_get_containers($page_id);
  foreach($containers as &$container) {


    if($container->fid) {
      // we need selector to do a parallaxa
      if(empty($container->wrapper_attributes['id'])) {
        $container->wrapper_attributes['id'] = 'infine-parallax-' . $container->id;
      }

      $selector = $container->wrapper_attributes['id'];
      $file = file_load($container->fid);
      $path = file_create_url($file->uri);

      foreach($container->wrapper_attributes as $attribute => $value) {
        if(!$value) {
            unset($container->wrapper_attributes[$attribute]);
        }
      }

      foreach($container->container_attributes as $attribute => $value) {
        if(!$value) {
          unset($container->container_attributes[$attribute]);
        }
      }

      drupal_add_css('#' . $selector . ' { background: url('.$path.') 0 0 no-repeat scroll !important; background-size: cover !important; }', 'inline');
    }


    $container->rows = infine_onepage_get_rows($container->id);

    foreach($container->rows as &$row) {
      $row->components  = infine_onepage_get_components($row->id);

      if(!$row->attributes['class']) {
        unset($row->attributes['class']);
      }

      if(!$row->attributes['id']) {
        unset($row->attributes['id']);
      }

      foreach($row->components as &$component) {

        $block = db_select('block', 'b')
          ->fields('b', array('module', 'delta'))
          ->condition('bid', $component->component_id)
          ->execute()->fetch();
        foreach($component->attributes['class'] as $index => $value) {
          if(!$value) {
            unset($component->attributes['class'][$index]);
          }
        }
        $block = block_load($block->module, $block->delta);

        $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
        $block = $render_array;

        $component->content = drupal_render($block);
      }
    }
  }

  $variables['containers'] = $containers;
}