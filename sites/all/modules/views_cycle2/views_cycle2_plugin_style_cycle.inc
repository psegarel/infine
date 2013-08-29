<?php

/**
 * @file
 * Contains the grid style plugin.
 */

/**
 * Style plugin to render each item in a grid cell.
 *
 * @ingroup views_style_plugins
 */
class views_cycle2_plugin_style_cycle extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['fx'] = array('default' => 'fade');
    $options['speed'] = array('default' => '500');
    $options['swipe'] = array('default' => TRUE);
    $options['timeout'] = array('default' => 4000);
    $options['show_pager'] = array('default' => TRUE);
    $options['allow-wrap'] = array('default' => TRUE);
    $options['auto-height'] = array('default' => 0);

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);


    $form['fx'] = array(
      '#type' => 'select',
      '#title' => t('Animation'),
      '#options' => array(
        'fade' => t('Fade'),
        'fadeout' => t('Fadeout'),
        'scrollHorz' => t('Horizontal scroll'),
        'scrollVert' => t('Vertical scroll'),
        'none' => t('None'),
      ),
      '#default_value' => $this->options['fx']
    );

    $form['swipe'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable swipe'),
      '#default_value' => $this->options['swipe']
    );

    $form['speed'] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#description' => t('Enter transition speed in milliseconds'),
      '#title' => t('Transition speed'),
      '#default_value' => $this->options['speed']
    );

    $form['timeout'] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#description' => t('Enter timeout time in milliseconds'),
      '#title' => t('Timeout'),
      '#default_value' => $this->options['timeout']
    );

    $form['allow-wrap'] = array(
      '#type' => 'checkbox',
      '#title' => t('Continuos loop'),
      '#description' => t('This option determines whether or not a slideshow can advance from the last slide to the first (or vice versa).'),
      '#default_value' => $this->options['allow-wrap']
    );

    $form['auto-height'] = array(
      '#type' => 'select',
      '#default_value' => $this->options['auto-height'],
      '#title' => t('Height'),
      '#options' => array(
        0 => t('Auto Resize'),
        'calc' => t('Calculation from tallest slide'),
      ),
      '#description' => t('This option determines whether or not Cycle2 will provide height management for the slideshow which can be very useful in fluid or responsive designs.'),
    );

    $form['show_pager'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show pager'),
      '#default_value' => $this->options['show_pager']
    );
  }
}
