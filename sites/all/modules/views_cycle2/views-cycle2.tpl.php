<div class="cycle2-container">
  <div class="cycle2-slider" data-cycle-pager="#<?php print $pager; ?>" data-cycle-slides="> .slides > div" <?php print drupal_attributes($slider_attributes); ?>>
    <div class="slides">
      <?php foreach ($rows as $delta => $row): ?>
        <div class="slide slide-cycle"><?php print $row; ?></div>
      <?php endforeach; ?>
    </div>
  </div>
  <?php if ($show_pager): ?>
    <div id="<?php print $pager; ?>" class="cycle-pager"></div>
  <?php endif; ?>
</div>


