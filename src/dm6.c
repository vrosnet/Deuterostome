/*

Copyright 2011 Alexander Peyser & Wolfgang Nonner

This file is part of Deuterostome.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
/*====================== D machine Rev3.0 (dm6.c) =======================

    - check FPU exception
          - checkFPU

    - monadic math operators
          - neg
          - abs
          - sqrt
          - exp
          - ln
          - lg
          - cos
          - sin
          - tan
          - atan
          - floor
          - ceil
          - acos
          - asin

    - universal copy/conversion operator
          - copy

    - dyadic math operators
          - add
          - sub
          - mul
          - div
          - pwr

    - VM operators / bind
          - save
          - restore
          - vmstatus
          - bind

    - class / type / attribute / conversion / string operators
          - class
          - type
          - readonly
          - active
	  - tilde
          - mkread
          - mkact
          - mkpass
	  - mktilde
          - ctype
          - parcel
          - text
          - number
          - token
          - search
          - anchorsearch

*/

#include "dm.h"

#include <string.h>
#include <stdio.h>

#include "dm6.h"
#include "dm2.h"
#include "dm8.h"

/*---------------------------------------------------- checkFPU
     -- | bool

  the boolean signals that an FPU exception has occurred since the
  last check; the exception is cleared.
*/

P op_checkFPU(void)
{
  if (o1 > CEILopds) return OPDS_OVF;
  TAG(o1) = BOOL; 
  ATTR(o1) = 0;
  BOOL_VAL(o1) = numovf;
  numovf = FALSE;
  FREEopds = o2;
  return OK;
}
  
/*---------------------------------------------------- dyadic
     num1 num2 | num1         - add to first scalar
    array1 num | array1       - add numeral to all array elements
 array1 array2 | array1       - add second array onto first

 No restriction on type; 'add' stands for any dyadic operation.
*/

static P dyadop(void)
{
  if (o_2 < FLOORopds) return OPDS_UNF;
  if (ATTR(o_2) & READONLY) return OPD_ATR;
  switch(CLASS(o_2))  { 
    case NUM:  
      switch(CLASS(o_1)) { 
        case NUM: break;
        case ARRAY: break;
        default: return OPD_CLA;
      }
      break;

    case ARRAY: 
      switch(CLASS(o_1)) { 
        case NUM: break;
        case ARRAY:
          if (ARRAY_SIZE(o_2) != ARRAY_SIZE(o_1))
            return RNG_CHK;
          break;
        default: return OPD_CLA;
      }
      break;

    default: 
      return OPD_CLA;
  }

  FREEopds = o_1;
  return OK;
}

P op_thearc(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  THEARC(o_1,o1);
  return OK;
}

P op_mod(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  MOD(o_1,o1);
  return OK;
}

P op_add(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  ADD(o_1,o1);
  return OK;
}

P op_sub(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  SUB(o_1,o1);
  return OK;
}

P op_mul(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  MUL(o_1,o1);
  return OK;
}

P op_div(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  DIV(o_1,o1);
  return OK;
}

P op_pwr(void)
{
  P retc;
  if ((retc = dyadop()) != OK) return retc;
  PWR(o_1,o1);
  return OK;
}

/*-------------------------------------------------- copy
   any1..anyn n | any1..anyn any1..anyn

copies n top elements of operand stack excluding n.

  array1 array2   | subarray2
    num1 array2   | array2
    list1 list2   | sublist2

copies all elements of the first composite object into the second,
starting at index zero of the destination (array or list), and returning
the subarray/list filled by the copy (the remainder of the destination
object is unaffected). The arrays/numeral may be of different types,
then invoking automatic conversion; an array may be copied into a
differently typed replica of itself, thus converting it in place
(towards a type of equal or smaller width). With a numeral in the
place of a first array, the numeral is expanded to fill the entire
destination array, which then is returned. The resulting object
inherits the destination attributes.

NB: internals only

*/

P op_copy(void)
{
  B *from, *cframe, cframebuf[FRAMEBYTES];
  P n;
  P nb;

  cframe = cframebuf;
  if (o_1 < FLOORopds) return OPDS_UNF;

  if (CLASS(o_1) == NUM) {          /* copy operand stack elements */
    if (!PVALUE(o_1,&n)) return UNDF_VAL;
    if (n < 0) return RNG_CHK;
    nb = n * FRAMEBYTES;
    if ((from = o_1 - nb) < FLOORopds) return RNG_CHK;
    if ((o_1 + nb) > CEILopds) return RNG_CHK;
    moveframes(from, o_1, n);
    FREEopds = o_1 + nb;
    return OK;
  }

  if (o_2 < FLOORopds) return OPDS_UNF;
  if (ATTR(o_1) & READONLY) return OPD_ATR;

  switch(CLASS(o_2)) {
    case NUM:
      switch (CLASS(o_1)) {
        case ARRAY:
          MOVE(o_2,o_1);
          moveframe(o_1,o_2);
          break;

        default: 
          return OPD_CLA;
      }
      break;
			 
    case ARRAY: 
      if (CLASS(o_1) != ARRAY) return OPD_CLA;
      if (ARRAY_SIZE(o_1) < ARRAY_SIZE(o_2)) return RNG_CHK;
      ARRAY_SIZE(o_1) = ARRAY_SIZE(o_2);
      MOVE(o_2,o_1);
      moveframe(o_1,o_2);
      ATTR(o_2) &= (~PARENT);
      break;

    case LIST: 
      if (CLASS(o_1) != LIST) return OPD_CLA;
      nb = LIST_CEIL(o_2) - VALUE_BASE(o_2);
      n = nb / FRAMEBYTES;
      if ( (n <=0) || ((LIST_CEIL(o_1) - VALUE_BASE(o_1)) < nb))
        return RNG_CHK;
      moveframes((B *)VALUE_BASE(o_2), (B *)VALUE_BASE(o_1), n);
      moveframe(o_1,o_2);
      LIST_CEIL(o_2) = VALUE_BASE(o_2) + nb;
      ATTR(o_2) &= (~PARENT);
      break;

    default: return OPD_CLA;
  }

  FREEopds = o_1;
  return OK;
}

/*---------------------------------------------------- monadic
     num | num
   array | array

 No restriction on type.
*/
static P monop(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  if (ATTR(o_1) & READONLY) return OPD_ATR;
  switch(CLASS(o_1)) { 
    case NUM: break;
    case ARRAY: break;
    default: return OPD_CLA;
  }
  return OK;
}

P op_neg(void)
{
  P retc;
  if ((retc = monop())) return retc;
  NEG(o_1);
  return OK;
}

P op_abs(void)
{
  P retc;
  if ((retc = monop())) return retc;
  ABS(o_1);
  return OK;
}

P op_sqrt(void)
{
  P retc;
  if ((retc = monop())) return retc;
  SQRT(o_1);
  return OK;
}

P op_exp(void)
{
  P retc;
  if ((retc = monop())) return retc;
  EXP(o_1);
  return OK;
}

P op_ln(void)
{
  P retc;
  if ((retc = monop())) return retc;
  LN(o_1);
  return OK;
}

P op_lg(void)
{
  P retc;
  if ((retc = monop())) return retc;
  LG(o_1);
  return OK;
}

P op_cos(void)
{
  P retc;
  if ((retc = monop())) return retc;
  COS(o_1);
  return OK;
}

P op_sin(void)
{
  P retc;
  if ((retc = monop())) return retc;
  SIN(o_1);
  return OK;
}

P op_tan(void)
{
  P retc;
  if ((retc = monop())) return retc;
  TAN(o_1);
  return OK;
}

P op_atan(void)
{
  P retc;
  if ((retc = monop())) return retc;
  ATAN(o_1);
  return OK;
}

P op_floor(void)
{
  P retc;
  if ((retc = monop())) return retc;
  FLOOR(o_1);
  return OK;
}

P op_ceil(void)
{
  P retc;
  if ((retc = monop())) return retc;
  CEIL(o_1);
  return OK;
}

P op_asin(void)
{
  P retc;
  if ((retc = monop())) return retc;
  ASIN(o_1);
  return OK;
}

P op_acos(void)
{
  P retc;
  if ((retc = monop())) return retc;
  ACOS(o_1);
  return OK;
}

/*----------------------------------------------- save
     --- | VM_box
     
  - creates a box object in VM
  - returns the box object
*/

P op_save(void)
{
  if (o1 >= CEILopds) return OPDS_OVF;
  if ((FREEvm + FRAMEBYTES + SBOXBYTES) > CEILvm) return VM_OVF;

  TAG(FREEvm) = BOX;
  ATTR(FREEvm) = PARENT;
  BOX_NB(FREEvm) = SBOXBYTES;
  VALUE_PTR(FREEvm) = FREEvm + FRAMEBYTES;
  moveframe(FREEvm, o1);
  FREEopds = o2;
  FREEvm += FRAMEBYTES;

  SBOX_CAP(FREEvm) = NULL;
  FREEvm += SBOXBYTES;

  return OK;
}

/*----------------------------------------------- capsave
     VM_box | ---
     
  - requires a box object from a preceding 'save'
  - modifies the box value to direct 'restore' to discard objects created
    between 'save' and 'capsave', retaining objects created following 'capsave'
*/

P op_capsave(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  if (CLASS(o_1) != BOX) return OPD_CLA;

  if (SBOX_CAP(VALUE_PTR(o_1))) return ILL_RECAP;
    
  SBOX_CAP(VALUE_PTR(o_1)) = FREEvm;
  FREEopds = o_1;

  return OK;
}

DM_INLINE_STATIC void shift_subframe(B* frame, P offset) 
{
  VALUE_PTR(frame) -= offset;
  if (CLASS(frame) == LIST) LIST_CEIL(frame) -= offset;
}

DM_INLINE_STATIC P clear_stack(B* savebox, B* caplevel, 
			       B** stack, B* stackfloor,
			       BOOLEAN capped) {
  B* topframe;
  B* cframe;
  
  for (topframe = cframe = *stack - FRAMEBYTES;
       cframe >= stackfloor;
       cframe -= FRAMEBYTES)
    if (COMPOSITE(cframe)
	&& (VALUE_PTR(cframe) >= savebox)
	&& (VALUE_PTR(cframe) <= caplevel)) {
      if (capped) return INV_REST;
      moveframes(cframe + FRAMEBYTES, cframe, 
		 (topframe-cframe)/FRAMEBYTES);
      topframe -= FRAMEBYTES;
      *stack -= FRAMEBYTES;
    }
  
  return OK;
}

DM_INLINE_STATIC void shift_stack(B* caplevel, P offset,
				  B* stack, B* stackfloor) {
  B* cframe;
  for (cframe = stack - FRAMEBYTES;
       cframe >= stackfloor;
       cframe -= FRAMEBYTES)
    if (COMPOSITE(cframe)
	&& (VALUE_PTR(cframe) > caplevel)
	&& (VALUE_PTR(cframe) <= CEILvm))
      shift_subframe(cframe, offset);
}

P (*cleanupfd_func)(void);
DM_INLINE_STATIC P check_wired(B* floor, B* top) {
  P retc;

  if (o2 > CEILopds) return OPDS_OVF;
  moveframe(floor, o1);
  FREEopds = o2;

 again:
  if (check_plugin && (retc = check_plugin())) return retc;
  if (cleanupfd_func && (retc = cleanupfd_func())) return retc;
  
  if ((retc = op_nextobject())) return retc;
  FREEopds = o_1;
  if (BOOL_VAL(o1)) {
    if (VALUE_PTR(o_1) - FRAMEBYTES < top) goto again;
    FREEopds = o_1;
  }

  return OK;
}
    
  
/*----------------------------------------------- restore
     VM_box | ---

  - requires a box object from a preceding 'save' (optionally capped by
    'capsave')
  - objects following 'box' in VM will be discarded up to the VM freespace
    (no cap) or to the VM level established by 'capsave'
  - terminates if the execution stack holds references to discardable objects
  - NOTE: uncapped saves handle objects on any stack in the save box
    by removing them from that stack.
  - if cap exists, moves down all objects located above the cap to repack VM;
    in the process, corrects masterframes and dictionary values for the offset
  - replaces discardable objects in retained lists by nulls, maintaining
    their 'active' attribute
  - removes associations to discardable objects (name and object) from
    retained dictionaries
  - adjusts VM freespace
  - NOTE: since we have in the linux version all operator dictionaries
    (system and external) stored ABOVE the VM ceiling, these need be
    exempted from address modifications made to shifted objects
  - NOTE: we no longer support restoration of operand and dictionary
    stacks from uncapped 'save' objects
 */
P op_restore(void)
{
  B *cframe, *frame, *dict, *tdict, *entry, *box, *savebox,
    *caplevel, *savefloor;
  P nb, offset;
  BOOLEAN capped;
  P retc;

  if (o_1 < FLOORopds) return OPDS_UNF;
  if (CLASS(o_1) != BOX) return OPD_CLA;
  savebox = VALUE_PTR(o_1);
  savefloor = savebox - FRAMEBYTES;
  if ((caplevel = SBOX_CAP(savebox))) capped = TRUE;
  else {
    capped = FALSE; 
    caplevel = FREEvm; 
  }
  if ((retc = check_wired(savefloor, caplevel))) return retc;

  offset = caplevel - savefloor;
  FREEopds = o_1;

  if ((retc = clear_stack(savebox, caplevel, &FREEexecs, FLOORexecs, capped)))
    return retc;
  if ((retc = clear_stack(savebox, caplevel, &FREEdicts, FLOORdicts, capped)))
    return retc;
  if ((retc = clear_stack(savebox, caplevel, &FREEopds, FLOORopds, capped)))
    return retc;

  if (capped)
    moveLBIG((LBIG*)caplevel, (LBIG*)savefloor, 
             (FREEvm - caplevel)/sizeof(LBIG));

  FREEvm -= offset;
  for (cframe = FLOORvm; cframe < FREEvm; ) switch(CLASS(cframe)) {
    case ARRAY: 
      nb = DALIGN(ARRAY_SIZE(cframe) * VALUEBYTES(TYPE(cframe)));
      if (VALUE_PTR(cframe) > caplevel) VALUE_PTR(cframe) -= offset;
      cframe += FRAMEBYTES + nb ; 
      break;
							
    case LIST:  
      if (VALUE_PTR(cframe) > caplevel && VALUE_PTR(cframe) <= CEILvm) {
	VALUE_BASE(cframe) -= offset; 
	LIST_CEIL(cframe) -= offset; 
      }
      for (frame = VALUE_PTR(cframe);
	   frame < LIST_CEIL_PTR(cframe); 
	   frame += FRAMEBYTES) {
	if (COMPOSITE(frame)) {  
	  if ((VALUE_PTR(frame) > caplevel) &&
	      (VALUE_PTR(frame) <= CEILvm)) { 
	    shift_subframe(frame, offset);
	  }
	  else if ((VALUE_PTR(frame) > savefloor) 
		   && (VALUE_PTR(frame) <= caplevel)) {
	    TAG(frame) = NULLOBJ; 
	    ATTR(frame) = 0; 
	  }
	}
      }
      cframe = (B *)LIST_CEIL(cframe); 
      break;

    case DICT:
      if (VALUE_PTR(cframe) > caplevel) { 
	VALUE_PTR(cframe) -= offset;
	d_reloc(VALUE_PTR(cframe),
		VALUE_BASE(cframe)+offset,
		VALUE_BASE(cframe));
      }
      dict = VALUE_PTR(cframe);
      if ((tdict = makedict((DICT_TABHASH(dict) - DICT_ENTRIES(dict))
			    / ENTRYBYTES)) == (B *)(-1L))
	return VM_OVF;
				
      for (entry = (B *)DICT_ENTRIES(dict);
	   entry < (B *)DICT_FREE(dict); 
	   entry += ENTRYBYTES) {
	frame = ASSOC_FRAME(entry);
	if (COMPOSITE(frame) && (VALUE_PTR(frame) <= CEILvm)) { 
	  if (VALUE_PTR(frame) > caplevel) { 
	    shift_subframe(frame, offset);
	  }
	  else if (VALUE_PTR(frame) > savefloor) continue;
	}
	insert(ASSOC_NAME(entry),tdict,frame);
      }
      d_rreloc(tdict,(P)tdict,(P)dict);
      moveLBIG((LBIG *)tdict, (LBIG *)dict, DICT_NB(cframe)/sizeof(LBIG));
      FREEvm = tdict - FRAMEBYTES;
      cframe += FRAMEBYTES + DICT_NB(cframe); 
      break;

    case BOX:
      if (VALUE_PTR(cframe) > caplevel) VALUE_PTR(cframe) -= offset;
      box = VALUE_PTR(cframe);
      if (SBOX_CAP(box)) { 
	if (SBOX_CAP(box) >= caplevel) SBOX_CAP(box) -= offset;
	else if (SBOX_CAP(box) > savefloor)
	  SBOX_CAP(box) = savefloor;
      }
      cframe += FRAMEBYTES + BOX_NB(cframe); 
      break;

    case STREAM:
      if (VALUE_PTR(cframe) > caplevel)
	VALUE_PTR(cframe) -= offset;
      cframe += FRAMEBYTES + STREAMBOXBYTES;
      break;

    default:
      return CORR_OBJ;
  };

  if (! capped) return OK;

  shift_stack(caplevel, offset, FREEexecs, FLOORexecs);
  shift_stack(caplevel, offset, FREEdicts, FLOORdicts);
  shift_stack(caplevel, offset, FREEopds, FLOORopds);

  return OK;
}

/*----------------------------------------------- vmstatus
   --- | max used
*/
P op_vmstatus(void)
{
  if (o2 >= CEILopds) return OPDS_OVF;

  TAG(o1) = TAG(o2) = NUM | LONGBIGTYPE;
  ATTR(o1) = ATTR(o2) = 0;
  LONGBIG_VAL(o1) = CEILvm - FLOORvm;
  LONGBIG_VAL(o2) = FREEvm - FLOORvm;
  FREEopds = o3;
  return OK;
}

/*----------------------------------------------- bind
   proc | proc

 - replaces executable names in proc that resolve to operators by their
   value
 - in addition, applies itself recursively to any not write-protected
   internal procedure nested in proc, and makes that procedure read-only
 - does not distinguish between system and dynamic operators
*/

DM_INLINE_STATIC P dmnamebind(B* nframe) {  
  B *xframe, *dframe, *dict;

  if (! ((ATTR(nframe) & (ACTIVE|TILDE)))
      || ATTR(nframe) & READONLY)
    return OK;

  xframe = NULL;
  for (dframe = FREEdicts - FRAMEBYTES; 
       dframe >= FLOORdicts;
       dframe -= FRAMEBYTES) { 
    dict = VALUE_PTR(dframe);
    if ((xframe = lookup(nframe,dict))) 
      break;
  }
  if (xframe && CLASS(xframe) == OP) {
    UB attr = ATTR(nframe);
    moveframe(xframe, nframe);
    if (attr & TILDE) {
      ATTR(nframe) |= TILDE;
      ATTR(nframe) &= ~ACTIVE;
    }
  }

  return OK;
}

// name bind conflicts with socket bind function, changed to dmbind
DM_INLINE_STATIC P dmprocbind(B *pframe)
{
  P retc; 
  B *frame;

  if ((ATTR(pframe) & (READONLY | ACTIVE)) != ACTIVE)
    return OK;

  for (frame = VALUE_PTR(pframe); 
       frame < LIST_CEIL_PTR(pframe);
       frame += FRAMEBYTES) 
    switch(CLASS(frame)) {
      case PROC: 
        if ((retc = dmprocbind(frame))) return retc; 
        break;

      case NAME: 
	if ((retc = dmnamebind(frame))) return retc;
	break;
    }

  ATTR(pframe) |= READONLY;
  return OK;
}

P op_bind(void)
{
  if (o_1 < FLOORopds) 
    return OPDS_UNF;

  switch (CLASS(o_1)) {
    case PROC: return dmprocbind(o_1);
    case NAME: return dmnamebind(o_1);
    default:   return OK;
  };
}

/*------------------------------------------- class
   object | /classname     (see below)
*/

P op_class(void)
{
  char *s;

  if (o_1 < FLOORopds) return OPDS_UNF;
  switch(CLASS(o_1)) {
    case NULLOBJ:  s = "nullclass"; break;
    case NUM:      s = "numclass"; break;
    case OP:       s = "opclass"; break;
    case NAME:     s = "nameclass"; break;
    case BOOL:     s = "boolclass"; break;
    case MARK:     s = "markclass"; break;
    case ARRAY:    s = "arrayclass"; break;
    case LIST:     s = "listclass"; break;
    case DICT:     s = "dictclass"; break;
    case BOX:      s = "boxclass"; break;
    case STREAM:   s = "streamclass"; break;
    default:       return CORR_OBJ;
  }
  makename((B*)s,o_1);
  return OK;
}

/*------------------------------------------- type
   object | /type (upper-case, one-letter code)
   NULLOBJ | /T (socket) or /N (none)
   DICT    | /O (oplibtype) or /X (opaque) or /N (none)
*/

P op_type(void)
{
  B c[2]; W key;

  if (o_1 < FLOORopds) return OPDS_UNF;

  switch (CLASS(o_1)) {
    case NULLOBJ:
      switch (TYPE(o_1)) {
	case SOCKETTYPE: *c = 'T'; break;
	case PIDTYPE:    *c = 'P'; break;
	default:         *c = 'N'; break;
      };
      break;

    case DICT:
      switch (TYPE(o_1)) {
        case OPLIBTYPE: *c = 'O'; break;
        case OPAQUETYPE: *c = 'Q'; break;
        default: *c = 'N'; break;
      };
      break;

    case NUM: case ARRAY:
      key = 0x4030 | TYPE(o_1);
      for (*c = 'A'; *c <= 'Z'; (*c)++) 
        if ((ascii[(*c) & 0x7F] & 0x403F) == key) 
          goto op79_1;
      return RNG_CHK;

    default:
      return OPD_CLA;
  };
 
 op79_1:
  c[1] = '\000'; makename(c,o_1);
  return OK;
}

/*------------------------------------------- readonly
     object | boolean       (reports 'read-only' attribute of frame)
*/

P op_readonly(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  BOOL_VAL(o_1) = (ATTR(o_1) & READONLY) ? TRUE : FALSE;
  TAG(o_1) = BOOL; 
  ATTR(o_1) = 0; 
  return OK;
}

/*------------------------------------------- active
     object | boolean       (reports 'active' attribute)
*/

P op_active(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  BOOL_VAL(o_1) = (ATTR(o_1) & ACTIVE) ? TRUE : FALSE;
  TAG(o_1) = BOOL; 
  ATTR(o_1) = 0;
  return OK;
}

/*---------------------------------------------- tilde
 * object | boolean (reports 'tilde' attribute)
 */

P op_tilde(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  BOOL_VAL(o_1) = (ATTR(o_1) & TILDE) ? TRUE : FALSE;
  TAG(o_1) = BOOL; 
  ATTR(o_1) = 0;
  return OK;
}

/*------------------------------------------- mkread
     object | readonly_object

 - marks the 'readonly' attribute in operand frame
*/

P op_mkread(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  ATTR(o_1) |= READONLY;
  return OK;
}

/*------------------------------------------- mkact
     object | active_object
*/

P op_mkact(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  ATTR(o_1) |= ACTIVE;
  ATTR(o_1) &= ~TILDE;
  return OK;
}

/*------------------------------------------ mkpass
     object | passive_object
*/

P op_mkpass(void)
{
  if (o_1 < FLOORopds) return OPDS_UNF;
  ATTR(o_1) &= ~(ACTIVE|TILDE);
  return OK;
}

/*----------------------------------------- mktilde
  object | tilded_object
*/

P op_mktilde(void) {
  if (o_1 < FLOORopds) return OPDS_UNF;
  ATTR(o_1) &= ~ACTIVE;
  ATTR(o_1) |= TILDE; 
  return OK;
}

/*------------------------------------------ ctype
     numeral /type | numeral       (type and value converted)
       array /type | array         (type converted, length adjusted)
*/

P op_ctype(void)
{
  B s[NAMEBYTES+1]; 
  W type;

  if (o_2 < FLOORopds) return OPDS_UNF;
  if (CLASS(o_1) != NAME) return OPD_ERR;

  pullname(o_1,s); 
  type = ascii[(*s) & 0x7F];
  if ((type & 0x4030) != 0x4030) return RNG_CHK; 
  type &= 0x0F;

  switch(CLASS(o_2)) {
    case NUM: 
      TAG(o_1) = NUM | type; 
      ATTR(o_1) = ATTR(o_2);
      MOVE(o_2,o_1); 
      moveframe(o_1,o_2);
      break;

     case ARRAY: 
       ARRAY_SIZE(o_2) = 
         (ARRAY_SIZE(o_2) * VALUEBYTES(TYPE(o_2))) / VALUEBYTES(type);
       TAG(o_2) = ARRAY | type; 
       ATTR(o_2) &= (~PARENT);
       break;

    default: 
      return OPD_CLA;
  }

  FREEopds = o_1;
  return OK;
}

/*------------------------------------------ parcel
     array1 length /type | remainder_of_array1 array2
  
  parcels array2 of given type and length from an initial subarray of
  array 1, which may be of different type (the returned arrays are
  word-aligned as necessary).
*/

P op_parcel(void)
{
  B s[NAMEBYTES+1]; W type;
  P length;
  P sadjust, badjust, nb;

  if (o_3 < FLOORopds) return OPDS_UNF;
  if ((CLASS(o_3) != ARRAY) || (CLASS(o_2) != NUM)) return OPD_CLA;
  if (CLASS(o_1) != NAME) return OPD_ERR;
  if (!PVALUE(o_2,&length)) return UNDF_VAL;
  if (length < 0) return RNG_CHK;

  pullname(o_1,s); 
  type = ascii[(*s) & 0x7F];
  if ((type & 0x4030) != 0x4030) return RNG_CHK; 
  type &= 0x0F;
  badjust = sadjust = 0;
  if (VALUEBYTES(type) & 1) { 
    if ((VALUEBYTES(TYPE(o_3)) & 1) == 0) sadjust = (length & 1); 
  }
  else  badjust = (VALUE_BASE(o_3) & 1);

  nb = length * VALUEBYTES(type) + badjust + sadjust;
  if ((ARRAY_SIZE(o_3) * VALUEBYTES(TYPE(o_3))) < nb) return RNG_CHK;
  TAG(o_2) = ARRAY | type; 
  ATTR(o_2) = ATTR(o_3) & (~PARENT);
  VALUE_BASE(o_2) = VALUE_BASE(o_3) + badjust;
  VALUE_BASE(o_3) += nb;
  ARRAY_SIZE(o_2) = length;
  ARRAY_SIZE(o_3) 
    = (ARRAY_SIZE(o_3) * VALUEBYTES(TYPE(o_3)) - nb) / VALUEBYTES(TYPE(o_3));

  FREEopds = o_1;
  return OK;
}

/*------------------------------------------ text
   string1 index signed_width/undef one_of_x | string1 new_index

   x = numeral / string / name / operator

 A non-string item x is converted to string form (numeral: used
 as ASCII code for one character; name: namestring is used; operator:
 operator name is used). The resulting string is copied into a field
 of given or corresponding (if undefined) width in string1 starting
 at the index. A negative width specifies left-adjustment within the 
 field. The unused part of the field receives spaces.  
*/

P op_text(void)
{
  B *src, *dest, code, sbuf[NAMEBYTES+1];
  P index, val, width;
  P length, start;

  if (o_4 < FLOORopds) return OPDS_UNF;
  if (ATTR(o_4) & READONLY) return OPD_ATR;
  if ((TAG(o_4) != (ARRAY | BYTETYPE)) || (CLASS(o_3) != NUM))
    return OPD_ERR;
  if (!PVALUE(o_3,(P*)&index)) return UNDF_VAL;
  if (index < 0) return RNG_CHK;

  switch(CLASS(o_1)) {
    case NUM: 
      if (!PVALUE(o_1,(P*)&val)) return UNDF_VAL;
      if ((val < 0) || (val > 255)) return UNDF_VAL;
      code = (B)val; 
      src = &code; 
      length = 1; 
      break;

    case OP: 
      src = (B*) OP_NAME(o_1); 
      length = strlen((char*)src); 
      break;

    case NAME: 
      src = sbuf; 
      pullname(o_1,src);
      length = strlen((char*)src); 
      break;
      
    case ARRAY: 
      if (TYPE(o_1) != BYTETYPE) return OPD_TYP;
      src = (B *)VALUE_BASE(o_1); 
      length = ARRAY_SIZE(o_1);
      break;
      
     default: 
       return OPD_CLA;
  }

  if (CLASS(o_2) != NUM) return OPD_CLA;
  if (!PVALUE(o_2, (P*)&width)) {width = length; start = index;}
  else { 
    if (width < 0) { width = -width; start = index; }
    else { start = index + width - length;}
    if (length > width) return RNG_CHK;
  }
  if ((index + width) > ARRAY_SIZE(o_4)) return RNG_CHK;
  TAG(o_3) = NUM | LONGBIGTYPE;
  LONGBIG_VAL(o_3) = index + width;
  dest = (B *)VALUE_BASE(o_4) + index;
  while (index < start) { *(dest++) = ' '; index++; width--; }
  while (length) { length--; *(dest++) = *(src++); width--; }
  while (width) { *(dest++) = ' '; width--; }

  FREEopds = o_2;
  return OK;
}

/*------------------------------------------ number
     string index signed_width/undef numeral format_int/undef |
     string new_index

 - sign of format integer selects between fixed-point (<0) and 
   floating-point (>0) formats; value gives precision (i.e. fractional
   digits); an undefined in this place selects automatic formatting. The
   precision is ignored for integer numerals.
*/

P op_number(void)
{
  static B buf[30];
  P prec = 0; 
  BOOLEAN fauto;

  if (o_2 < FLOORopds) return OPDS_UNF;
  if (CLASS(o_1) != NUM) return OPD_CLA;
  if (!PVALUE(o_1,&prec)) fauto = TRUE;
  else {
    if ((prec < -17) || (prec > 17)) return RNG_CHK; 
    fauto = FALSE;
  }
  if (CLASS(o_2) != NUM) return OPD_CLA;

  DECODE(o_2, fauto, prec, buf);
  TAG(o_2) = ARRAY | BYTETYPE; 
  ATTR(o_2) = READONLY;
  VALUE_BASE(o_2) = (P) buf; 
  ARRAY_SIZE(o_2) = strlen((char*)buf);
  FREEopds = o_1;
  return op_text();
}

/*------------------------------------------ token
     string/stream | remainder_of_string/stream object true
                     string false
*/    

P (*tokenfd_func)(void) = NULL;

P op_token(void)
{
  P retc; 
  BOOLEAN bool;

  if (o_1 < FLOORopds) return OPDS_UNF;
  switch (TAG(o_1)) {
    case ARRAY|BYTETYPE:
      switch ((retc = tokenize(o_1))) {
	case OK:   bool = TRUE; break;
	case DONE: bool = FALSE; break;
	default:   return retc;
      }
      break;

    case STREAM: 
      if (!tokenfd_func) return OPD_CLA;
      switch ((retc = tokenfd_func())) {
	case OK:   bool = TRUE;  break;
	case DONE: bool = FALSE; break;
	default:   return retc;
      }
      break;

    default:
      return OPD_CLA;
  };
  if (o1 >= CEILopds) return OPDS_OVF;

  TAG(o1) = BOOL; 
  ATTR(o1) = 0;
  BOOL_VAL(o1) = bool;
  FREEopds = o2;
  return OK;
}

/*--------------------------------------------- search
   string seek | if found: post match pre true
               | else:     string false

  - searches string for substring seek; divides string on success
*/

P op_search(void)
{
  UB *string, *xstring, *seek;
  P nstring, nseek;

  if (o_2 < FLOORopds) return OPDS_UNF;
  if ((TAG(o_2) != (ARRAY | BYTETYPE)) 
      || (TAG(o_1) != (ARRAY | BYTETYPE))) 
    return OPD_ERR;
  if (ARRAY_SIZE(o_2) == 0) goto op90_f;
  if (ARRAY_SIZE(o_1) == 0) return RNG_CHK;
  string = (UB *)VALUE_BASE(o_2); 
  nstring = ARRAY_SIZE(o_2);

 op90_1:
  seek = (UB *)VALUE_BASE(o_1); nseek = ARRAY_SIZE(o_1);
  while (nstring >= nseek) { 
    if ((*string) == (*seek)) goto op90_2; 
    string++; nstring--; 
  }
  goto op90_f;

 op90_2:
  nseek--; 
  xstring = string + 1; 
  nstring--;
  while (nseek) { 
    if ((*(xstring++)) != (*(++seek))) { string++; goto op90_1; }
    nseek--;
  }
  if (o2 >= CEILopds) return OPDS_OVF;
  
  moveframe(o_2,o1);
  ARRAY_SIZE(o1) = (P)string - VALUE_BASE(o1);
  VALUE_BASE(o_1) = (P)string;
  VALUE_BASE(o_2) = (P)xstring;
  ARRAY_SIZE(o_2) = nstring - ARRAY_SIZE(o_1) + 1;
  ATTR(o_2) &= ~PARENT;
  ATTR(o1) = ATTR(o_1) = ATTR(o_2);
  TAG(o2) = BOOL; ATTR(o2) = 0;
  BOOL_VAL(o2) = TRUE;
  FREEopds = o3;
  return OK;

 op90_f:
  TAG(o_1) = BOOL; ATTR(o_1) = 0; BOOL_VAL(o_1) = FALSE;
  return OK;
}

/*--------------------------------------------- anchorsearch
   string seek | if found: post match true
               | else:     string false

  - tests string for initial substring seek; divides string on success
*/

P op_anchorsearch(void)
{
  UB *string, *seek;
  P nstring, nseek;

  if (o_2 < FLOORopds) return OPDS_UNF;
  if ((TAG(o_2) != (ARRAY | BYTETYPE)) 
      || (TAG(o_2) != (ARRAY | BYTETYPE))) 
    return OPD_ERR;

  if (ARRAY_SIZE(o_2) == 0) goto op91_f;
  if (ARRAY_SIZE(o_1) == 0) return RNG_CHK;
  string = (UB *)VALUE_BASE(o_2); 
  nstring = ARRAY_SIZE(o_2);
  seek = (UB *)VALUE_BASE(o_1); 
  nseek = ARRAY_SIZE(o_1);
  if (nstring < nseek) goto op91_f;

  while (nseek) { 
    if (*(string++) != *(seek++)) goto op91_f;
    nseek--;
  }
  if (o1 >= CEILopds) return OPDS_OVF;

  nseek = ARRAY_SIZE(o_1);
  moveframe(o_2,o_1); 
  ARRAY_SIZE(o_1) = nseek;
  VALUE_BASE(o_2) += nseek; 
  ARRAY_SIZE(o_2) -= nseek;
  ATTR(o_2) &= ~PARENT; 
  ATTR(o_1) = ATTR(o_2);
  TAG(o1) = BOOL; 
  ATTR(o1) = 0; 
  BOOL_VAL(o1) = TRUE;
  FREEopds = o2;
  return OK;

 op91_f:
  TAG(o_1) = BOOL; 
  ATTR(o_1) = 0; 
  BOOL_VAL(o_1) = FALSE;
  return OK;
}

/*-------------------- op_socketval -------------------
  socket | int

  convert to socket fd number for debuggin
*/


P op_socketval(void) {
  P val;
  if (o_1 < FLOORopds) return OPDS_UNF;
  if (TAG(o_1) != (NULLOBJ|SOCKETTYPE)) return OPD_ERR;

  val = SOCKET_VAL(o_1);
  TAG(o_1) = (NUM|LONGBIGTYPE);
  ATTR(o_1) = 0;
  LONGBIG_VAL(o_1) = val;

  return OK;
}
