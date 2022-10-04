# drupaldrushpolicy

Allow developers to run limited Drush commands against a Drupal 7 production environment.

## How to use

create a basic user. With no other configuration applied
this lets a dev run basic commands and see 90% of what
needs to be seen. This is read only. It's not possible
for this user to run any command that could damage the system
adduser drushremoteuser

## set a password

passwd drushremoteuser

But Devs still need limited Drush access to the system
## Add the user to the Apache group. 

This let's the user run any script that the
Apache web server can run

usermod -a -G apache drushremoteuser

The user can now run Drush commands against the production server

#

BUT THIS IS DANGEROUS - some Drush commands can nuke the system

## Copy the referenced PHP code into the new user's home directory

This DENIES execution to all Drush commands initially, and then
ALLOWS execution based on inclusion in a white list

## copy paste policy.drush.inc to drushremoteuser directory under ~/.drush/

Copy and paste policy.drush.inc into the home directory of 'drushremoteuser' 
under ~/.drushrc. IMPORTANT: Set the ownership and permissions so the
user can read it, but not edit it.

- chown root:root ~/.drush/policy.drush.inc
- chmod 440 ~/.drush/policy.drush.inc

## Add commands to the whitelist as needed. All other commands will be blocked

ex, add cache-clear to allow clearing cache

vi /home/remotedrush/.drush/policy.drush.inc
