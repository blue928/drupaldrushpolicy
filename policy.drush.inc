<?php
/**
 * @file
 *
 * Prevent unauthorized commands from being executed against a remote Production
 * Drupal web server
 *
*/
function policy_drush_init() {
  $current = drush_get_command();
  $lists = _get_lists();

  $user =  'Current script owner is '.get_current_user().' with UID '.getmyuid().' and GID '.getmygid().'';

  drush_set_error('Message', $user);
  if (in_array($current['command'], $lists['blacklist'])) {
    _blacklisted();
  }
  else if (!in_array($current['command'], $lists['whitelist'])) {
    return drush_set_error('NEED_ADMIN', dt('You cannot run this command. Contact your sys admin.'));
  }
}
  // it's not blacklisted, if it's not whitelisted it must need certain
  // user privileges. Replacing the above 'else if' statement with the below
  // allows a sys admin to run any non-blacklisted command.
  //
  // else if (!in_array($current['command'], $lists['whitelist'])) {
  //  _needs_root();
  // }
  //
  // see the accompanying function below
  

/**
 * To run Drush commands not explicitly in the whitelisted list,
 * check for elevated prvileges. 
 *
 * @return void
 *
function _needs_root() {
    if (drush_is_windows()) {
      // TODO: implement check for elevated process in Windows
    }
    else {
      $name = posix_getpwuid(posix_geteuid());
      # TODO switch to check uid == 0 instead
      if ($name['name'] !== 'root') {
        return drush_set_error('NEED_ROOT', dt('You cannot run this command as the current user.'));
      }
    }
}
*/

/**
 * Get a list of all Drush commands to check against
 * 
 * This allows us to DENY access to ALL Drush commands
 * initially, and then incrementally ALLOW given a 
 * list of safe, whitelisted commands.
 * 
 * Commands that are not explicitly in either list mean
 * a root / sysadmin can still run it.
 *
 * Blacklisted commands cannot be ran by anyone, not
 * even root
 *
 * @return void
 */
function _get_lists() {
  return array(
    // NEVER EVER RUN THESE COMMANDS - EVER!!!
    // We don't want anyone ever to drop the database.
    // Not even sys admins running as root can run these.
    'blacklist' => array(
      'sql-drop',
      'php-eval',
    ),
    // These commands can be run by anyone on the system.
    // The name must be the fully qualifed command name, not
    // the alias; e.g. 'cache-clear' not 'cc'
    'whitelist' => array(
      'help',
      'status',
      'cache-clear',
      'sql-dump',
    ),
  );
}

/**
 * Return an error message and log an entry when an
 * attempt is made to run a black listed command.
 *
 * @return void
 */
function _blacklisted(){
  $msg = 'YOU MAY NOT RUN A BLACKLISTED COMMAND - THIS ACTIVITY HAS BEEN LOGGED';
  return drush_set_error('BLACKLISTED', dt($msg));
}

/*
 * Customize this file as desired. See https://github.com/drush-ops/drush/blob/8.x/examples/policy.drush.inc for documentation.
 */
