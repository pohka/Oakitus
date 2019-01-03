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


## ui
* having more padding than set height, does not act like box-sizing: border-box;, it should not expand larger than the set height
  * e.g. padding(20,20); height=10;
* UIImage dont resize when padding is added, instead it acts like margin pushing it
* UILabel doesnt have an auto height, the height should be calculated from the height a character with the font
* auto width doesnt work for any UINodes

# engine
shaders dont have destructor
font characters dont delete from glbuffers