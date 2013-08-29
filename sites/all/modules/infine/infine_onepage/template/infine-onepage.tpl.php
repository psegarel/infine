<?php

?>

<div id="<?php print $page_id; ?>" class="onepage-page">
  <h2><?php print $page->title ?></h2>

  <div id="infine-container-<?php print $page->id; ?>-sort" class="infine-sortable">

    <?php foreach ($containers as $container): ?>
      <?php print $container; ?>
    <?php endforeach; ?>
  </div>

  <?php print $add_form; ?>
</div>
