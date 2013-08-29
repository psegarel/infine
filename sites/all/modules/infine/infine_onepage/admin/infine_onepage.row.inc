<?php

/**
 * Form for adding and editing components
 * @param $form
 * @param $form_state
 * @param $container
 * @param null $row
 * @return mixed
 */
function infine_onepage_form_component($form, &$form_state, $row, $component = NULL) {
  $ids = _infine_onepage_get_ids($row, 'row');

  if ($component) {
    $ids = _infine_onepage_get_ids($component, 'component');
  }
  $form['#id'] = $ids['form_id'];

  $ids = _infine_onepage_get_ids($row, 'row');
  $create_new = isset($form_state['values']['create_new']) ? $form_state['values']['create_new'] : FALSE;

  $form['row'] = array(
    '#type' => 'value',
    '#value' => $row,
  );

  $form['wrapper'] = array(
    '#type' => 'container',
  );

  if (!$component && !$create_new) {
    $form['wrapper']['add'] = array(
      '#type' => 'submit',
      '#value' => t('Add component'),
      '#submit' => array('infine_onepage_form_ajax_container'),
      '#name' => $ids['form_id'],
      '#ajax' => array(
        'wrapper' => $ids['form_id'],
        'callback' => 'infine_onepage_form_ajax_container',
      )
    );

    $form['wrapper']['remove'] = array(
      '#value' => t('Remove row'),
      '#type' => 'submit',
      '#name' => $ids['wrapper_id'] . '-remove',
      '#required' => TRUE,
      '#submit' => array('infine_onepage_form_ajax_reload'),
      '#ajax' => array(
        'wrapper' => $ids['wrapper_id'],
        'callback' => 'infine_onepage_form_ajax_row_remove',
        'method' => 'replace',
      )
    );
  }
  else {

    $form['wrapper']['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => isset($component->name) ? $component->name : '',
    );

    $form['wrapper']['attributes'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
      '#attributes' => array(
        'class' => array('inline'),
      )
    );

    $form['wrapper']['attributes']['id'] = array(
      '#title' => t('ID'),
      '#type' => 'textfield',
      '#required' => TRUE,
      '#default_value' => isset($component->attributes['id']) ? $component->attributes['id'] : '',
    );

    $form['wrapper']['attributes']['class']['span'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#options' => array(
        '' => t('Fullwidth'),
        'span1' => t('1 Column'),
        'span2' => t('2 Column'),
        'span3' => t('3 Column'),
        'span4' => t('4 Column'),
        'span5' => t('5 Column'),
        'span6' => t('6 Column'),
        'span7' => t('7 Column'),
        'span8' => t('8 Column'),
        'span9' => t('9 Column'),
        'span10' => t('10 Column'),
        'span11' => t('11 Column'),
        'span12' => t('12 Column'),
      ),
      '#default_value' => isset($component->attributes['class']['span']) ? $component->attributes['class']['span'] : 0,
    );

    $form['wrapper']['attributes']['class']['offset'] = array(
      '#type' => 'select',
      '#title' => t('Offset'),
      '#options' => array(
        0 => t('No offset'),
        'offset1' => t('1 Column'),
        'offset2' => t('2 Column'),
        'offset3' => t('3 Column'),
        'offset4' => t('4 Column'),
        'offset5' => t('5 Column'),
        'offset6' => t('6 Column'),
        'offset7' => t('7 Column'),
        'offset8' => t('8 Column'),
        'offset9' => t('9 Column'),
        'offset10' => t('10 Column'),
        'offset11' => t('11 Column'),
      ),
      '#default_value' => isset($component->attributes['class']['offset']) ? $component->attributes['class']['offset'] : 0,
    );


    $options = infine_onepage_get_block_info();
    $form['wrapper']['component_id'] = array(
      '#title' => t('Select block'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => isset($component->component_id) ? $component->component_id : reset(array_keys($options)),

    );

    $form['wrapper']['component'] = array(
      '#type' => 'value',
      '#value' => $component,
    );


    $form['wrapper']['actions'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('form-actions'),
      )
    );

    $form['wrapper']['actions']['submit'] = array(
      '#value' => empty($component) ? t('Create component') : t('Save'),
      '#type' => 'submit',
      '#name' => $ids['wrapper_id'],
      '#required' => TRUE,
      '#submit' => array('infine_onepage_form_ajax_component_submit'),
//      '#ajax' => array(
//        'wrapper' => $ids['wrapper_id'],
//        'callback' => 'infine_onepage_form_ajax_component_submit',
//        'method' => 'replace',
//      )
    );

    if ($component) {
      $form['wrapper']['actions']['delete'] = array(
        '#value' => t('Delete'),
        '#type' => 'submit',
        '#name' => $ids['wrapper_id'] . '-delete',
        '#required' => TRUE,
        '#submit' => array('infine_onepage_form_ajax_reload'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'wrapper' => $ids['wrapper_id'],
          'callback' => 'infine_onepage_form_ajax_component_delete',
          'method' => 'replace',
        )
      );
    }
  }

  return $form;
}

/**
 * @param $form
 * @param $form_state
 * @return string
 */
function infine_onepage_form_ajax_component_submit($form, &$form_state) {
  $component = $form_state['values']['component'];

  $form_state['values']['attributes'] = serialize($form_state['values']['attributes']);
  $form_state['values']['container_id'] = $form_state['values']['row']->id;
  $form_state['values']['component'] = 'block';

  $keys = array();
  if ($component) {
    $form_state['values']['id'] = $component->id;
    $keys = array('id');
  }

  // create new row
  drupal_write_record('infine_onepage_component', $form_state['values'], $keys);
  $row = $form_state['values']['row'];

  // load new form
  $form = drupal_get_form('infine_onepage_form_component_' . $row->id, $row);

  // replace old container
//  return theme('infine_onepage_row', array('row' => $row, 'add_form' => $form));
}

function infine_onepage_form_ajax_component_delete($form, &$form_state) {
  $component = $form_state['values']['component'];

  db_delete('infine_onepage_component')->condition('id', $component->id)->execute();
  drupal_set_message('Deleted');

  $row = $form_state['values']['row'];

  // load new form
  $form = drupal_get_form('infine_onepage_form_component_' . $row->id, $row);

  // replace old container
  return theme('infine_onepage_row', array('row' => $row, 'add_form' => $form));
}

function infine_onepage_form_ajax_row_remove($form, &$form_state) {

  $id = $form_state['values']['row']->id;

  db_delete('infine_onepage_row')
    ->condition('id', $id)
    ->execute();

  db_delete('infine_onepage_component')
    ->condition('container_id', $id)
    ->execute();

  // replace old container
  return '';
}

function infine_onepage_system_info_alter(&$info, $file, $type) {

  if ($type == 'theme') {
    $info['regions']['header'] = t('Region name');
  }
}


function infine_onepage_form_ajax_edit($form, &$form_state) {
  $form_state['values']['edit'] = TRUE;
  $form_state['rebuild'] = TRUE;

  return $form;
}
