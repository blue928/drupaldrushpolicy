# drupaldrushpolicy

#### TODO clean this up. It's currently written for a personal, specific use. This is for Linux - todo, figure out a windows solution

Allow developers to run limited Drush commands against a Drupal 7 production environment.

## How to use

## Create a basic user. 
```
adduser drushremoteuser
```

## Set a password
```
passwd drushremoteuser
```

But Devs still need limited Drush access to the system
## Add the user to the Apache group. 

This let's the user run any script that the
Apache web server can run

```
usermod -a -G apache drushremoteuser
```

The user can now run Drush commands against the production server


BUT THIS IS DANGEROUS - some Drush commands can nuke the system.
You don't even want your root user or sysadmin to be able to run
commands like 'sql-drop.' I've seen it happen - sql-dump -y, sql-drop -y 
muscle memory is a helluva thing for the efficient developer.


## Copy policy.drush.inc to drushremoteuser $HOME directory under ~/.drush/

TODO: mention other locations where drush searches for config files, test which
one is most secure.

This DENIES execution to all Drush commands initially, and then
ALLOWS their execution based on inclusion in a white list

Copy and paste policy.drush.inc into the home directory of 'drushremoteuser' 
under ~/.drushrc. IMPORTANT: Set the ownership and permissions so the
user can read it, but not edit it.

```
chown root:root ~/.drush/policy.drush.inc
chmod 444 ~/.drush/policy.drush.inc
# TODO test which perms and which Drush config directory option is most secure.
```

## Add commands to the whitelist as needed. All other commands will be blocked

TODO (possibly) create a yaml file or something easier to reference than having
to include these directly in the PHP file.

ex, add cache-clear to allow clearing cache

vi /home/remotedrush/.drush/policy.drush.inc
