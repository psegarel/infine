<?php

/**
 * Implements hook_form_alter()
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function infine_utils_form_alter(&$form, &$form_state, $form_id) {

  //@todo Damn ! :(
  if($form_id == 'webform_client_form_19') {


    $form['submitted']['your_name']['#attributes']['placeholder'] = $form['submitted']['your_name']['#title'];
    unset($form['submitted']['your_name']['#title']);
    $form['submitted']['your_name']['#prefix'] ="<div class=row><div class=\"control span4\">";
    $form['submitted']['your_name']['#suffix'] ="<span class=\"icon icon-normal-profile-male\"></span></div>";


    $form['submitted']['your_email']['#attributes']['placeholder'] = $form['submitted']['your_email']['#title'];
    unset($form['submitted']['your_email']['#title']);
    $form['submitted']['your_email']['#prefix'] = "<div class=\"control span4\">";
    $form['submitted']['your_email']['#suffix'] ="<span class=\"icon icon-normal-mail\"></span></div></div>";


    $form['submitted']['message']['#attributes']['placeholder'] = $form['submitted']['message']['#title'];
    $form['submitted']['message']['#resizable'] = FALSE;
    $form['submitted']['message']['#prefix'] =  "<div class=\"row\"><div class=\"control span8\">";
    $form['submitted']['message']['#suffix'] =  "<span class=\"icon icon-normal-pencil\"></span></div></div>  ";


    
    unset($form['submitted']['message']['#title']);
  }

  if ($form_id == 'features_node_form') {
    $node = & $form['#node'];

    $form['class'] = array(
      '#type' => 'select',
      '#title' => t('Color scheme'),
      '#options' => arraY(
        0 => t('None'),
        'orange' => t('Orange'),
        'blue' => t('Blue'),
        'yellow' => t('Yellow'),
      ),
      '#default_value' => isset($node->class) ? $node->class : 0,
    );

    $form['#submit'][] = 'infine_utils_form_alter_submit';
  }
}

/**
 * @param $form
 * @param $form_state
 */
function infine_utils_form_alter_submit($form, &$form_state) {
  $node = $form['#node'];
  $node->class = $form_state['values']['class'];
}

/**
 * Implements hook_node_insert
 * @param $node
 */
function infine_utils_node_insert($node) {
  if ($node->type == 'features') {
    if (isset($node->class)) {
      $record['class'] = $node->class;
    }
    else {
      return;
    }

    if (isset($node->nid)) {

      $record['nid'] = $node->nid;
      $class = _infine_utils_load_class($node->nid);

      if(isset($class['id'])) {
        $record['id'] = $class['id'];
      }
    }
    else {
      return;
    }

    if (isset($record['id'])) {
      drupal_write_record('infine_feature_class', $record, 'id');
    }
    else {
      drupal_write_record('infine_feature_class', $record);
    }
  }
}

/**
 * Implements hook_node_update
 * @param $node
 */
function infine_utils_node_update($node) {
  infine_utils_node_insert($node);
}

/**
 * @param $nodes
 * @param $types
 */
function infine_utils_node_load($nodes, $types) {
  if (in_array('features', $types)) {
    foreach ($nodes as &$node) {
      $node->class = _infine_utils_load_class($node->nid);

    }
  }
}

/**
 * @param $nid
 * @return array
 */
function _infine_utils_load_class($nid) {
  $result = db_select('infine_feature_class', 'rcc')
    ->condition('nid', $nid)
    ->fields('rcc')
    ->execute()->fetchAssoc();

  if ($result) {
    return $result;
  }

  return array();
}

function _infine_utils_save_class() {

}