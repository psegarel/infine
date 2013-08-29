<div id="wrapper">
  <div id="wrapper-inner">


    <div class="navigation">
      <div class="navbar navbar-fixed-top">
        <div class="navbar-inner">

          <div class="container">
            <div class="row">
              <div id="#nav-header" class="span4">
                <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
                  <span class="icon-bar"></span>
                  <span class="icon-bar"></span>
                  <span class="icon-bar"></span>
                </a>

                <?php if ($logo || $site_name): ?>
                  <div class="logo">

                    <a class="logo-img" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
                      <img src="<?php print $logo; ?>"/>
                    </a>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
                      <?php if ($site_name): ?>
                        <?php print $site_name; ?>
                      <?php endif; ?>
                    </a>
                  </div><!-- /.logo -->
                <?php endif; ?>



                <?php if ($site_slogan): ?>
                  <div class="site-slogan">
                    <span><?php print $site_slogan; ?></span>
                  </div><!-- /.site-slogan -->
                <?php endif; ?>
              </div>
              <div class="span8 main-navigation nav-collapse collapse">
                <?php if (!empty($page['navigation'])): ?>
                  <div class="navigation-wrapper">
                    <div class="navigation clearfix">
                      <?php print render($page['navigation']); ?>
                    </div>
                    <!-- /.navigation -->
                  </div><!-- /.navigation-wrapper -->
                <?php endif; ?>
              </div>
            </div>

            <!-- /.main-navigation -->
          </div>
          <!-- /.container -->
        </div>
        <!-- /.navbar-inner -->
      </div>
      <!-- /.main-navigation -->
    </div>
    <!-- /.navigation -->

    <div id="main-content" class="container">
      <div class="row">
        <?php if ($page['sidebar']): ?>
          <div id="sidebar" class="span3">
            <?php print render($page['sidebar']); ?>
          </div>
        <?php endif; ?>

        <div id="main" class="<?php if ($page['sidebar']) {
          print "span9";
        }
        else {
          print 'span12';
        } ?>">
          <?php print render($title_prefix); ?>
          <?php if (!empty($title)): ?>
            <h1 class="page-header"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php print $messages; ?>
          <?php if (!empty($tabs)): ?>
            <?php print render($tabs); ?>
          <?php endif; ?>
          <?php if (!empty($page['help'])): ?>
            <div class="well"><?php print render($page['help']); ?></div>
          <?php endif; ?>
          <?php if (!empty($action_links)): ?>
            <ul class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>
          <?php print render($page['content']) ?>


        </div>
      </div>
    </div>


    <div id="nav-contact" class="footer-wrapper">
      <div class="footer container">
        <div class="footer-inner">
          <div class="row">
            <?php if ($page['footer_right']): ?>
              <div class="item span4">
                <?php print drupal_render($page['footer_left']); ?>
              </div>
            <?php endif; ?>
            <!-- /.item -->

            <?php if ($page['footer_right']): ?>
              <div class="item span8">
                <?php print drupal_render($page['footer_right']); ?>
              </div>
            <?php endif; ?>
            <!-- /.item -->
          </div>
          <!-- /.row -->
        </div>
        <!-- /.footer-inner -->
      </div>
      <!-- /.footer -->
      <?php if ($page['map']): ?>
        <div id="map">
          <?php print render($page['map']); ?>
        </div>
      <?php endif; ?>
      <div class="footer-bottom">
        <div class="container">
          <div class="row">
            <?php if ($page['copyright']): ?>
              <div class="span9 copyright">
                <?php print drupal_render($page['copyright']); ?>
              </div>
            <?php endif; ?>

            <?php if ($page['social_icons']): ?>
              <div class="span3 icons">
                <?php print drupal_render($page['social_icons']); ?>
              </div>
            <?php endif; ?>


            <!-- /.icons -->
          </div>
          <!-- /.row -->
        </div>
        <!-- /.container -->
      </div>
      <!-- /.footer bottom -->
    </div>
  </div>
</div>