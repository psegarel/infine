<div <?php print drupal_attributes($formatter_attributes); ?>>

  <?php foreach ($chunks as $parent): ?>

    <div class="field-item" style="clear: both; margin-bottom: 20px">
      <?php if (isset($parent['parent'])): ?>
        <label style="margin-left: 30px; font-weight: bold;">
          <?php print $parent['parent']; ?>
        </label>
      <?php endif ?>

      <?php foreach ($parent['terms'] as $terms): ?>
        <ul <?php print drupal_attributes($chunk_attributes); ?>>
          <?php foreach ($terms as $term): ?>
            <li <?php print drupal_attributes($term['attributes']); ?>>
              <?php print $term['value']; ?>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endforeach; ?>
    </div>
  <?php endforeach; ?>
</div>
