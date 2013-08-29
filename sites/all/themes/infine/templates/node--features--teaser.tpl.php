<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="row">
        <div class="wrapper-icon span1">
            <div class="background-icon">
                <?php print drupal_render($content['field_icon']); ?>
            </div>
            <!-- /.background-icon -->
        </div>
        <!-- /.wrapper-icon -->

        <?php
          // Hide comments, tags, and links now so that we can render them later.
          hide($content['links']);
        ?>

        <div class="text-wrapper span3">
          <?php print render($title_prefix); ?>
          <?php if (!$page && $title): ?>
            <h3<?php print $title_attributes; ?>><?php print $title; ?></h3>
          <?php endif; ?>
          <?php print render($title_suffix); ?>

            <div class="features-description">
              <?php print render($content); ?>
            </div>
        </div>
    </div>
</div>
<!-- /.node -->
