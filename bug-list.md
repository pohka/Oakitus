# Bug List

## Projectile does multiple damage instances when entered twice
* projectile.deleteOnHit = false
* projectile collisionHit with unit
* projectile stops overlapping
* unit moves back into the projectile
* does a 2nd instance of damage
* animations and casting times dont slow down with timescale
* if there is no ability assigned to a slot, crashes. should have a fallback
* sprites probably leak memeory because of GL_STATIC_DRAW and other opengl stuff, look at sprite_animation.cpp for fix

