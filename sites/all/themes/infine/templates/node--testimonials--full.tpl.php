<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php print render($title_suffix); ?>

  <div class="span2 testimonials-image center item">
    <div class="testimonials-image-box">
      <?php print render($content['field_image']); ?>
    </div>
  </div>


  <div class="span6 item">
    <?php print render($content['body']); ?>
  </div>

  <div class="span3">
    <?php print render($content['about']); ?>
  </div>

  <?php
  // Hide comments, tags, and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  hide($content['field_tags']);
  print render($content);
  ?>
  <?php print render($content['comments']); ?>

</div> <!-- /.node -->
