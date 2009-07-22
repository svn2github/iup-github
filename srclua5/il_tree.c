/******************************************************************************
 * Automatically generated file (iuplua5). Please don't change anything.                *
 *****************************************************************************/

#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>

#include "iup.h"
#include "iuplua.h"
#include "il.h"


static int tree_branchopen_cb(Ihandle *self, int p0)
{
  lua_State *L = iuplua_call_start(self, "branchopen_cb");
  lua_pushnumber(L, p0);
  return iuplua_call(L, 1);
}

static int tree_selection_cb(Ihandle *self, int p0, int p1)
{
  lua_State *L = iuplua_call_start(self, "selection_cb");
  lua_pushnumber(L, p0);
  lua_pushnumber(L, p1);
  return iuplua_call(L, 2);
}

static int tree_dragdrop_cb(Ihandle *self, int p0, int p1, int p2, int p3)
{
  lua_State *L = iuplua_call_start(self, "dragdrop_cb");
  lua_pushnumber(L, p0);
  lua_pushnumber(L, p1);
  lua_pushnumber(L, p2);
  lua_pushnumber(L, p3);
  return iuplua_call(L, 4);
}

static int tree_rename_cb(Ihandle *self, int p0, char * p1)
{
  lua_State *L = iuplua_call_start(self, "rename_cb");
  lua_pushnumber(L, p0);
  lua_pushstring(L, p1);
  return iuplua_call(L, 2);
}

static int tree_renamenode_cb(Ihandle *self, int p0, char * p1)
{
  lua_State *L = iuplua_call_start(self, "renamenode_cb");
  lua_pushnumber(L, p0);
  lua_pushstring(L, p1);
  return iuplua_call(L, 2);
}

static int tree_showrename_cb(Ihandle *self, int p0)
{
  lua_State *L = iuplua_call_start(self, "showrename_cb");
  lua_pushnumber(L, p0);
  return iuplua_call(L, 1);
}

static int tree_multiselection_cb(Ihandle *self, int p0, int p1)
{
  lua_State *L = iuplua_call_start(self, "multiselection_cb");
  lua_pushnumber(L, p0);
  lua_pushnumber(L, p1);
  return iuplua_call(L, 2);
}

static int tree_branchclose_cb(Ihandle *self, int p0)
{
  lua_State *L = iuplua_call_start(self, "branchclose_cb");
  lua_pushnumber(L, p0);
  return iuplua_call(L, 1);
}

static int tree_executeleaf_cb(Ihandle *self, int p0)
{
  lua_State *L = iuplua_call_start(self, "executeleaf_cb");
  lua_pushnumber(L, p0);
  return iuplua_call(L, 1);
}

static int tree_rightclick_cb(Ihandle *self, int p0)
{
  lua_State *L = iuplua_call_start(self, "rightclick_cb");
  lua_pushnumber(L, p0);
  return iuplua_call(L, 1);
}

static int tree_noderemoved_cb(Ihandle *self, int p0, char * p1)
{
  lua_State *L = iuplua_call_start(self, "noderemoved_cb");
  lua_pushnumber(L, p0);
  lua_pushstring(L, p1);
  return iuplua_call(L, 2);
}

static int Tree(lua_State *L)
{
  Ihandle *ih = IupTree();
  iuplua_plugstate(L, ih);
  iuplua_pushihandle_raw(L, ih);
  return 1;
}

void iuplua_treefuncs_open(lua_State *L);

int iuptreelua_open(lua_State * L)
{
  iuplua_register(L, Tree, "Tree");

  iuplua_register_cb(L, "BRANCHOPEN_CB", (lua_CFunction)tree_branchopen_cb, NULL);
  iuplua_register_cb(L, "SELECTION_CB", (lua_CFunction)tree_selection_cb, NULL);
  iuplua_register_cb(L, "DRAGDROP_CB", (lua_CFunction)tree_dragdrop_cb, NULL);
  iuplua_register_cb(L, "RENAME_CB", (lua_CFunction)tree_rename_cb, NULL);
  iuplua_register_cb(L, "RENAMENODE_CB", (lua_CFunction)tree_renamenode_cb, NULL);
  iuplua_register_cb(L, "SHOWRENAME_CB", (lua_CFunction)tree_showrename_cb, NULL);
  iuplua_register_cb(L, "MULTISELECTION_CB", (lua_CFunction)tree_multiselection_cb, NULL);
  iuplua_register_cb(L, "BRANCHCLOSE_CB", (lua_CFunction)tree_branchclose_cb, NULL);
  iuplua_register_cb(L, "EXECUTELEAF_CB", (lua_CFunction)tree_executeleaf_cb, NULL);
  iuplua_register_cb(L, "RIGHTCLICK_CB", (lua_CFunction)tree_rightclick_cb, NULL);
  iuplua_register_cb(L, "NODEREMOVED_CB", (lua_CFunction)tree_noderemoved_cb, NULL);

  iuplua_treefuncs_open(L);

#ifdef IUPLUA_USELOH
#ifdef TEC_BIGENDIAN
#ifdef TEC_64
#include "loh/tree_be64.loh"
#else
#include "loh/tree_be32.loh"
#endif
#else
#ifdef TEC_64
#ifdef WIN64
#include "loh/tree_le64w.loh"
#else
#include "loh/tree_le64.loh"
#endif
#else
#include "loh/tree.loh"
#endif
#endif
#else
  iuplua_dofile(L, "tree.lua");
#endif

  return 0;
}

