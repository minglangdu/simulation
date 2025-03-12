# Object Attributes
The following is a list of attributes that objects may have:
*Italic* characters aren't part of the attribute name and are comments.

**DIFFICULTY** (integer): how much movement in terrain is slowed.

---

*Only a difficulty of -1 makes it impossible to go to the square*<br>
*Positive difficulties hinder movement but cannot stop it completely*
*(there is a minimum)*
<br><br>

**DESCRIPTION** (string): unused as of now, self-explanatory.

---

*Just a description.*
<br><br>

**TILE** (string): The tile used to represent an object.

---

*The default texture should be a `?`.*
<br><br>

**ZLEVEL** (integer): Which order objects should appear when rendering the scene.

---

*A higher Z level means the object will be displayed higher. The default Z level should be 0.*
<br><br>

**CONSTRUCTION** (boolean): dictates whether something is a construction.

---

*Constructions can't be moved, only deconstructed, like buildings and constructions in Dwarf Fortress.*
<br><br>

**TERRAIN** (boolean): dictates whether it can be used as a piece of terrain in a location.

---

*Terrain is a special object that can be used as the ground of a location. Terrain is similarly unmovable like a construction.*
<br><br>

**INCORPOREAL** (boolean): dictates whether the object can be passed through or not. 