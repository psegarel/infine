<?php

function infine_onepage_form_onepage($form , &$form_state, $page = NULL) {

  $form['page'] = array(
    '#type' => 'value',
    '#value' => $page,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Title'),
    '#default_value' => isset($page->title) ? $page->title : '',
  );

  $form['path'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Path'),
    '#default_value' => isset($page->path) ? $page->path : '',
  );

  $form['attributes'] = array(
    '#tree' => TRUE,
  );

  $form['attributes']['id'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('ID'),
    '#default_value' => isset($page->attributes['id']) ? $page->attributes['id'] : '',
  );

  $form['attributes']['class'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Class'),
    '#default_value' => isset($page->attributes['class']) ? $page->attributes['class'] : '',
  );

  $form['actions'] = array(
    '#type' => 'container',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('infine_onepage_form_onepage_submit')
  );

  if($page) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('infine_onepage_form_onepage_delete')
    );
  }

  return $form;
}

function infine_onepage_form_onepage_submit($form, &$form_state) {
  $form_state['values']['attributes'] = serialize($form_state['values']['attributes']);
  $page = $form_state['values']['page'];

  $keys = array();
  if($page) {
    $form_state['values']['id'] = $page->id;
    $keys = array('id');
  }

  drupal_write_record('infine_onepage', $form_state['values'], $keys);
  drupal_set_message(t('Onepage saved'));

  $form_state['redirect'] = 'admin/structure/onepage';
}



function infine_onepage_form_onepage_delete($form, &$form_state) {
  $page = $form_state['values']['page'];

  $form_state['redirect'] = 'admin/structure/onepage/' . $page->id . '/delete';
}

function infine_onepage_form_onepage_delete_confirm($form , &$form_state, $page) {
  $form['page'] = array(
    '#type' => 'value',
    '#value' => $page,
  );

  $return_path = 'admin/structure/onepage';

  return confirm_form(
    $form,
    t('Are you sure you want to remove this page: "!name" ?', array('!name' => $page->title)),
    $return_path
  );
}

function infine_onepage_form_onepage_delete_confirm_submit($form , &$form_state) {

  $page = $form_state['values']['page'];
  $form_state['redirect'] = 'admin/structure/onepage/';

  db_delete('infine_onepage')->condition('id', $page->id)->execute();

  drupal_set_message(t('Page deleted'));
}


/**
 * @param $page_id
 * @return string
 */
function infine_onepage_page_admin($page_id) {
  $page = db_select('infine_onepage', 'io')
    ->fields('io', array())
    ->condition('id', $page_id)
    ->execute()->fetch();

  $add_form = drupal_get_form('infine_onepage_form_container', $page);
  return theme('infine_onepage', array('page' => $page, 'add_form' => $add_form));
}

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function infine_onepage_form_table($form, &$form_state) {
  $components = infine_onepage_get_all_components();
  $form['#tree'] = TRUE;

  $form['components'] = array(
    '#type' => 'value',
    '#value' => $components,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  foreach ($components as $id => $component) {
    $form['weight'][$id] = array(
      '#type' => 'textfield',
      '#default_value' => $id,
      '#attributes' => array(
        'class' => array('infine-weight-group'),
      )
    );
  }

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function infine_onepage_form_table_submit($form, &$form_state) {
  $data = $form_state['values'];
  $components = infine_onepage_get_all_components();

  foreach ($data['weight'] as $id => $weight) {
    $component = $components[$id];

    $edit = array(
      'id' => $id,
      'weight' => $weight,
    );

    $mlid = db_select('menu_links', 'ml')
      ->fields('ml', array('mlid'))
      ->condition('link_path', 'node/' . $component->component_id)
      ->execute()->fetchColumn();

    if($mlid) {
      $menu_link = menu_link_load($mlid);
      $menu_link['options']['attributes']['name'] = '#component-' . $component->id;
    } else {

      $menu_link = array(
        'menu_name' => 'main-menu',
        'plid' => 0,
        'link_path' => '#',
        'router_path' => '',
      );

      $menu_link['options']['attributes']['name'] = '#component-' . $component->id;
    }

    menu_link_save($menu_link);
    drupal_write_record('infine_onepage', $edit, 'id');
  }
}


function theme_infine_onepage_form_table(&$variables) {
  $output = '';

  $form = $variables['form'];
  $components = $form['components']['#value'];

  $header = array(t('ID'), t('Component'), t('Component ID'));
  $rows = array();

  foreach ($components as $id => $component) {
    $row = array(
      array(
        'data' => $component->component
      ),
      array(
        'data' => $component->component_id
      ),
      array(
        'data' => render($form['weight'][$id])
      ),
    );

    $rows[$id] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }


  $output .= theme(
    'table',
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'id' => 'infine-onepage-table',
      ),
    )
  );

  $output .= drupal_render_children($form);
  drupal_add_tabledrag('infine-onepage-table', 'order', 'sibling', 'infine-weight-group');

  return $output;
}