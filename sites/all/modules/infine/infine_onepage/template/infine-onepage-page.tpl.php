<?php

?>

<?php foreach ($containers as $container): ?>

<div <?php print drupal_attributes($container->wrapper_attributes); ?>>
    <div <?php print drupal_attributes($container->container_attributes); ?>>
        <div <?php print drupal_attributes($container->inner_attributes); ?>>

          <?php foreach ($container->rows as $row): ?>
            <div <?php print drupal_attributes($row->attributes); ?>>
              <?php foreach ($row->components as $component): ?>
                <div <?php print drupal_attributes($component->attributes); ?>>
                  <?php print $component->content; ?>
                </div>
              <?php endforeach; ?>
            </div>
          <?php endforeach; ?>
        </div>
    </div>
</div>

<?php endforeach; ?>