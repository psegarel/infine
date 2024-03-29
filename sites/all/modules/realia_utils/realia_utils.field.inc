<?php

/**
 *
 */
function realia_utils_field_formatter_info() {
  return array(
    'taxonomy_reference_full' => array(
      'label' => t('Realia reference'),
      'field types' => array('taxonomy_term_reference'),
      'settings' => array(
        'width' => 'row',
        'column_wrapper' => 'span2',
        'columns' => 4
      ),
    )
  );
}

function realia_utils_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'taxonomy_reference_full') {

    $element['width'] = array(
      '#title' => t('Wrapper class'),
      '#type' => 'textfield',
      '#default_value' => $settings['width'],
      '#required' => TRUE,
    );

    $element['column_wrapper'] = array(
      '#title' => t('Wrapper class for column'),
      '#type' => 'textfield',
      '#default_value' => $settings['column_wrapper'],
      '#required' => TRUE,
    );

    $element['columns'] = array(
      '#title' => t('Number of columns'),
      '#type' => 'select',
      '#options' => array(
        1 => 1,
        2 => 2,
        3 => 3,
        4 => 4,
        5 => 5,
      ),
      '#default_value' => $settings['columns'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#required' => TRUE,
    );

  }

  return $element;
}

function realia_utils_field_formatter_settings_summary($field, $instance, $view_mode) {
  $settings = $instance['display'][$view_mode]['settings'];

  $lines[] = t('Class: !class', array('!class' => $settings['width']));
  $lines[] = t('Column wrapper: !class', array('!class' => $settings['column_wrapper']));
  $lines[] = t('Number of columns: !number', array('!number' => $settings['columns']));

  return implode('<br />', $lines);
}


function realia_utils_field_formatter_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {

  $tids = array();
  $settings = $field['settings'];
  $vocabulary = $settings['allowed_values'][0]['vocabulary'];

  $query = db_select('taxonomy_term_data', 'ttd');
  $query->leftJoin('taxonomy_term_hierarchy', 'tth', 'tth.tid = ttd.tid');
  $query->addField('tth', 'parent', 'parent');
  $query->leftJoin('taxonomy_vocabulary', 'tv', 'tv.vid = ttd.vid');
  $query->fields('ttd', array('tid', 'name'));
  $query->condition('tv.machine_name', $vocabulary);

  $all_options = $query->execute()->fetchAllAssoc('tid');


  foreach ($items as $delta => $item) {
    // Force the array key to prevent duplicates.
    $tids[$item['tid']] = $item['tid'];
  }

  $terms = array();

  foreach ($all_options as $tid => $option) {

    $terms[$option->parent][$tid]['value'] = $option->name;
    $terms[$option->parent][$tid]['checked'] = FALSE;

    if (isset($tids[$tid])) {
      $terms[$option->parent][$tid]['checked'] = TRUE;
    }
  }


  $build = array(
    '#theme' => 'realia_taxonomy_formatter',
    '#terms' => $terms,
    '#settings' => $displays['settings'],
  );

  $element = array();
  $element += $build;

  return $element;
}


