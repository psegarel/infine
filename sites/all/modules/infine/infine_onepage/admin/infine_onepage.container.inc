<?php

function _infine_onepage_get_ids($element, $type) {
  return array(
    'form_id' => 'infine-' . $type . '-' . $element->id,
    'wrapper_id' => 'infine-' . $type . '-' . $element->id . '-wrapper'
  );
}

/**
 * Form for adding and editing rows
 * @param $form
 * @param $form_state
 * @param $container
 * @param null $row
 * @return mixed
 */
function infine_onepage_form_row($form, &$form_state, $container, $row = NULL) {
  $ids = _infine_onepage_get_ids($container, 'container');
  $form['#id'] = $ids['form_id'];

  $create_new = isset($form_state['values']['create_new']) ? $form_state['values']['create_new'] : FALSE;

  $form['container'] = array(
    '#type' => 'value',
    '#value' => $container,
  );

  $form['wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => $ids['form_id'] . '-form-wrapper',
    )
  );

  if (!$row && !$create_new) {

    $form['wrapper']['add'] = array(
      '#type' => 'submit',
      '#value' => t('Add new row'),
      '#submit' => array('infine_onepage_form_ajax_container'),
      '#name' => $ids['form_id'],
      '#ajax' => array(
        'wrapper' => $ids['form_id'] . '-form-wrapper',
        'callback' => 'infine_onepage_form_ajax_container',
        'method' => 'replace',
      )
    );

    $form['wrapper']['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove container'),
      '#submit' => array('infine_onepage_form_ajax_container_remove'),
      '#name' => $ids['wrapper_id'] . '-remove',
//      '#ajax' => array(
//        'wrapper' => $ids['wrapper_id'],
//        'callback' => 'infine_onepage_form_ajax_container_remove',
//        'method' => 'replace',
//      )
    );
  }
  else {

    $form['wrapper']['attributes'] = array(
      '#tree' => TRUE,
    );

    $form['wrapper']['attributes']['id'] = array(
      '#title' => t('ID'),
      '#type' => 'textfield',
    );

    $form['wrapper']['attributes']['class'] = array(
      '#title' => t('Class'),
      '#type' => 'textfield',
    );

    $form['wrapper']['submit'] = array(
      '#value' => t('Create'),
      '#type' => 'submit',
      '#name' => $ids['wrapper_id'],
      '#required' => TRUE,
      '#submit' => array('infine_onepage_form_ajax_row_submit'),
//      '#ajax' => array(
//        'wrapper' => $ids['wrapper_id'],
//        'callback' => 'infine_onepage_form_ajax_row_submit',
//        'method' => 'replace',
//      )
    );
  }

  return $form;
}

/**
 * Dummy ajax callback for submitting forms
 * @param $form
 * @param $form_state
 */
function infine_onepage_form_ajax_row_submit($form, &$form_state) {
  $form_state['values']['attributes'] = serialize($form_state['values']['attributes']);
  $form_state['values']['container_id'] = $form_state['values']['container']->id;

  // create new row
  drupal_write_record('infine_onepage_row', $form_state['values']);
  $container = $form_state['values']['container'];

  // load new form
  $form = drupal_get_form('infine_onepage_form_row_' . $container->id, $container);

  // replace old container
//  return theme('infine_onepage_container', array('container' => $container, 'add_form' => $form));
}

/**
 * @param $form
 * @param $form_state
 * @return string
 */
function infine_onepage_form_ajax_reload(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

function infine_onepage_form_ajax_container_remove($form, &$form_state) {
  $id = $form_state['values']['container']->id;

  $row_ids = db_select('infine_onepage_row', 'ior')
    ->fields('ior', array('id'))
    ->condition('container_id', $id)
    ->execute()->fetchCol();

  db_delete('infine_onepage_container')
    ->condition('id', $id)
    ->execute();

  db_delete('infine_onepage_row')
    ->condition('container_id', $id)
    ->execute();

  if ($row_ids) {
    db_delete('infine_onepage_component')
      ->condition('container_id', $row_ids, 'IN')
      ->execute();
  }
}
