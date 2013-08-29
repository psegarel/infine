<?php

?>

<div id="<?php print $container_id; ?>" class="container-wrapper">

  <div class=<?php print $container_class?>>

    <div class="row">
      <div class="span12">
        <?php print $container->name; ?>

        <a class="container-action-edit" href="#<?php print $form_id; ?>"></a>
      </div>
    </div>

    <div class="component-form hidden">
      <div class="row">
        <div class="span12">
          <?php print drupal_render($container_form); ?>
        </div>
      </div>
    </div>

    <?php if (count($rows)): ?>
        <div id="infine-row-<?php print $container->id; ?>-sort" class="infine-sortable">
          <?php foreach ($rows as $row): ?>
            <?php print $row; ?>
          <?php endforeach; ?>
      </div>
    <?php endif; ?>

    <?php print $add_form; ?>
  </div>
</div>
