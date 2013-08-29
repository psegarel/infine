<?php

function infine_onepage_form_container($form, &$form_state, $page, $container = NULL) {

  if ($container) {
    $ids = _infine_onepage_get_ids($container, 'container');
  }
  else {
    $ids = _infine_onepage_get_ids($page, 'page');
  }

  $form['#id'] = $ids['form_id'];
  $form['#attributes']['style'] = array('padding: 30px;');

  $ids = _infine_onepage_get_ids($page, 'page');
  $create_new = isset($form_state['values']['create_new']) ? $form_state['values']['create_new'] : FALSE;

  $form['page'] = array(
    '#type' => 'value',
    '#value' => $page,
  );
  $form['container'] = array(
    '#type' => 'value',
    '#value' => $container,
  );

  $form['#prefix'] = "<div class=\"row\">";
  $form['#suffix'] = "</div>";

  if (!$container && !$create_new) {
    $form['add'] = array(
      '#type' => 'submit',
      '#value' => t('Add new container'),
      '#name' => $ids['form_id'],
      '#submit' => array('infine_onepage_form_ajax_container'),
      '#ajax' => array(
        'wrapper' => $ids['form_id'],
        'callback' => 'infine_onepage_form_ajax_container',
      )
    );

  }
  else {
    $form['generic'] = array(
      '#type' => 'container',
      '#prefix' => "<div class=span4>",
      '#suffix' => "</div>",
    );

    $form['generic']['image'] = array(
      '#type' => 'managed_file',
      '#title' => t('Background image'),
      '#default_value' => isset($container->fid) ? $container->fid : NULL,
      '#upload_location' => 'public://infine_container/',
      '#description' => t('Use this only if you intend  to use this section as parallax')
    );

    $form['generic']['fullwidth'] = array(
      '#type' => 'checkbox',
      '#title' => t('Full Width'),
      '#weight' => 0,
      '#default_value' => isset($container->fullwidth) ? $container->fullwidth : 0,
    );

    $form['generic']['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#required' => TRUE,
      '#default_value' => isset($container->name) ? $container->name : '',
    );

    $form['attributes'] = array(
      '#tree' => TRUE,
    );

    $form['attributes']['wrapper'] = array(
      '#title' => t('Wrapper'),
      '#type' => 'fieldset',
      '#prefix' => "<div class=span3>",
      '#suffix' => "</div>",
    );

    $form['attributes']['wrapper']['id'] = array(
      '#title' => t('ID'),
      '#type' => 'textfield',
      '#default_value' => isset($container->attributes['wrapper']['id']) ? $container->attributes['wrapper']['id'] : '',
    );

    $form['attributes']['wrapper']['class'] = array(
      '#title' => t('Class'),
      '#type' => 'textfield',
      '#default_value' => isset($container->attributes['wrapper']['class']) ? $container->attributes['wrapper']['class'] : '',
    );

    $form['attributes']['container'] = array(
      '#title' => t('Container'),
      '#type' => 'fieldset',
      '#prefix' => "<div class=span3>",
      '#suffix' => "</div>",
    );

    $form['attributes']['container']['id'] = array(
      '#title' => t('ID'),
      '#type' => 'textfield',
      '#default_value' => isset($container->attributes['container']['id']) ? $container->attributes['container']['id'] : '',
    );

    $form['attributes']['container']['class'] = array(
      '#title' => t('Class'),
      '#type' => 'textfield',
      '#default_value' => isset($container->attributes['container']['class']) ? $container->attributes['container']['class'] : '',
    );

    $form['actions'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('form-actions'),
        'style' => array('clear:both;'),
      )
    );

    $ids = _infine_onepage_get_ids($page, 'page');

    $form['actions']['submit'] = array(
      '#value' => empty($container) ? t('Create container') : t('Save'),
      '#type' => 'submit',
      '#name' => $ids['wrapper_id'] . '-' . $container->id,
      '#required' => TRUE,
      '#submit' => array('infine_onepage_form_ajax_container_submit'),
    );
  }

  return $form;
}

function infine_onepage_form_ajax_container_submit($form, &$form_state) {
  $container = $form_state['values']['container'];
  $form_state['values']['attributes'] = serialize($form_state['values']['attributes']);
  $form_state['values']['page_id'] = $form_state['values']['page']->id;

  if($form_state['values']['image']) {
    $file = file_load($form_state['values']['image']);
    $file->status = FILE_STATUS_PERMANENT;
    $form_state['values']['fid'] = $file->fid;
  }

  $keys = array();
  if ($container) {
    $keys = array('id');
    $form_state['values']['id'] = $container->id;
  }

  drupal_write_record('infine_onepage_container', $form_state['values'], $keys);
  $page = $form_state['values']['page'];

  if(isset($form_state['values']['fid'])) {
    file_usage_add($file, 'revolution_slide', 'revolution_slide', $container->id);
  }
}

