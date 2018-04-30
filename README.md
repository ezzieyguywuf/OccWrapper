# OccWrapper

### How to compile

```bash
git clone --recurse-subprojects https://github.com/ezzieyguywuf/OccWrapper
cd OccWrapper
mkdir build
cd build
make -j8 all
make test # if you want to run the tests
```

### What is it?

OccWrapper is intended to be used as an abstraction layer for OpenCasCade (see? OCC?). It
is being written specifically with FreeCAD in mind, but should work just as well for any
other project that wishes to use the functionalities of OpenCasCade.

### Why?

OpenCasCade is a great library, and provides lot's of features to its users.
Unfortunately, it is also a very old code base, with lots of legacy code and classes, many
of which are obsolete and have been replaced with new (better?) options. The old stuff has
been kept around for backwards compatibility (I guess).

Aside from that, OpenCasCade can also be a bit bearish to work with at times. Say you have
a `TopoDS_Solid`, let's call it `mySolid`. How does one figure out how many faces are in
`mySolid`? I guess:

```cpp
TopoDS_Solid mySolid = GetMySolid(); // get it from wherever
// create a container for the faces;
TopTools_IndexedMapOfShapes faces;
// fill the container
TopExp::Explorer(mySolid, TopAbs_FACE, faces);
// Get the number of faces
std::cout << "mySolid has " << faces.Extent()
          << " faces" << std::endl;
// how do we iterate this?
for (int i=1; i<= faces.Extent() ; i++)
{
    TopoDS_Face aFace = faces.FindKey(i);
}
```

"Oh, that wasn't so painful" you might be thinking. And I guess you'd be right. But what
about if I just performed a boolean fusion using a `BRepAlgoAPI_Fuse` object, let's call
it `mkFuse`, and I want to retrieve a list of the faces which, say, the first face in
`mySolid` was modified to? hrm, not so easy...

```cpp
BRepAlgoAPI_Fuse mkFuse(mySolid, myOtherSolid);
mkFuse.Build()
// so, we still need a list of our faces...
TopTools_IndexedMapOfShapes faces;
TopExp::Explorer(mySolid, TopAbs_FACE, faces);
// except, the return value of mkFuse.Modified is not a TopTools_IndexedMapOfShapes...
TopTools_ListOfShape modified = mkFuse.Modified(faces.FindKey(1));
// now, how do we access these modified faces again?
TopTools_ListIteratorOfListOfShape it(modifie);
for(; it.More(); it.Next())
{
    TopoDS_Face aFace = it.Current();
}
```

Man. This is confusing. I have different container types, one of them has a helper
iterator class, and honestly I just can't keep it all straight. This was the primary
impetus for OccWrapper, literally because I couldn't keep this all straight. Here's how
you would perform these same tasks using OccWrapper:

```cpp
TopoDS_Solid mySolid = GetMySolid()
Occ::Solid myOccSolid(mySolid);
// Get the number of faces
std::cout << "mySolid has " << myOccSolid.getFaces().size()
          << " faces" << std::endl;
// getFaces returns a std::vector so...
for (const Occ::Face& aFace : myOccSolid.getFaces())
{
    // do something with aFace
}
```

What about the whole `mkFuse.Modified` thing? Well, we have a wrapper for that:

```cpp
BRepAlgoAPI_Fuse mkFuse(mySolid, myOtherSolid);
Occ::BooleanSolid myFusion = Occ::SolidMaker::MakeBoolean(mkFuse);
const Occ::ModifiedSolid& myModifiedSolid = myFusion.getModifiedSolids()[0];
// getModifiedFaceIndices returns a vector of unsigned ints, so...
for (uint i : myModifiedSolid.getModifiedFaceIndices(mySolid.getFaces()[0])))
{
    const Occ::Face aFace = mySolid.getFaces()[i];
    // do something with aFace
}
```

Why does `getModifiedFaceIndices` return a vector if `int` instead of a vector of
`Occ::Face`? Because, in my use cases (i.e. in TopoManagers) I needed the indices more
often than I needed the faces themselves.

## Project Status

The project is in its infancy. It is barely started. I don't even have an `Occ::Vertex`
wrapper. At this point, it is mostly a proof-of-concept to show how an OpenCasCade wrapper
could be used in order to make working with occ less painful. It has also been used in the
development of the TopoManagers library.

## TODO
* eliminate all the stored vectors and just used `TopExp::MapShapes` or w/e each time
  someone calls `getFaces` or `getEdges`.
* Add `Occ::Vertx`
* to be continued...
