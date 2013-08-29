<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="row">
      <?php
          // Hide comments, tags, and links now so that we can render them later.
          hide($content['links']);
        ?>

        <div class="image-box span5">
            <div class="image">
              <?php print render($content['field_image']); ?>
            </div>
        </div>

        <div class="span7">
          <?php print render($title_prefix); ?>
          <?php if (!$page && $title): ?>
            <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
          <?php endif; ?>
          <?php print render($title_suffix); ?>
            <div class="features-description">
              <?php print render($content); ?>
            </div>
        </div>
    </div>
</div>
<!-- /.node -->
