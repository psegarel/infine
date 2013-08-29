<?php

?>

<div id="<?php print $row_id; ?>" class="<?php print $row_class; ?> visible">

    <div class="<?php print $span_class;?>">
        <div class="<?php print $row_class; ?> title">
            <div class="<?php print $span_class;?>">
                <?php print t('Row'); ?>
            </div>
        </div>

        <div class="<?php print $row_class; ?>">
            <div class="infine-sortable">
              <?php foreach ($components as $component): ?>
              <?php print $component; ?>
              <?php endforeach; ?>
            </div>
        </div>

        <div class="<?php print $row_class; ?> component-forms">

          <?php foreach($component_forms as $form): ?>
            <div class="component-form hidden">
              <?php print drupal_render($form); ?>
            </div>
          <?php endforeach; ?>

        </div>

        <div class="<?php print $row_class; ?> form">
            <div class="<?php print $span_class;?>">
              <?php print $add_form ?>
            </div>
        </div>
    </div>
</div>