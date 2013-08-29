<div class="row speaker <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php print render($title_suffix); ?>

    <div class="span2 image center">
        <div class="image-box">
          <?php print render($content['field_speaker_image']); ?>
        </div>
    </div>


    <div class="span7">
      <?php print render($content['field_presenter']); ?>
      <?php print render($content['field_presenters_title']); ?>

        <div class="talk-title">
          <?php print $title; ?>
        </div>

      <?php print render($content['field_session_time']); ?>
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
