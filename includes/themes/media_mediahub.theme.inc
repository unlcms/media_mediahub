<?php

/**
 * @file media_mediahub/includes/themes/media_mediahub.theme.inc
 *
 * Theme and preprocess functions for Media: MediaHub.
 */

/**
 * Preprocess function for theme('media_mediahub_video').
 */
function media_mediahub_preprocess_media_mediahub_video(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = check_plain($parts['media']);
  $variables['query'] = array();

  $variables['url_api'] = 'media/' . $variables['video_id'] . '/file';
  $variables['url'] = url('http://mediahub.unl.edu/' . $variables['url_api'] , array('query' => $variables['query'], 'external' => TRUE, 'https' => TRUE));

  $service_base_url = 'http://mediahub.unl.edu/';
  $service_media_link = $service_base_url . 'media/'.$variables['video_id'];

  //set the default output (fall back to just a link)
  $variables['output'] = '<a href="' . $service_media_link . '">Media</a>';

  //Try to get the embed code via the API
  $json = json_decode(@file_get_contents($service_media_link.'?format=json'));
  if (isset($json->url)) {
    $variables['output'] = $json->embed;
  }
}
