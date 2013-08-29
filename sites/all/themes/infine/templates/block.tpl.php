<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
	<div class="title">
	  <?php print render($title_prefix); ?>

	  <?php if ($title): ?>
	    <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
	  <?php endif;?>
	  <?php print render($title_suffix); ?>
	</div><!-- /.title -->

  <div class="content">
  	<?php print $content ?>
  </div><!--   /.content -->
</div><!-- /.block -->
