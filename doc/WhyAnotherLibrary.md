# Why another library?

The Smart Game Format is a decades old, established file format. There are many Go applications out there that have to deal with SGF files. Surely someone else has already written a reusable C/C++ software library for reading and writing SGF files. Right?

Alas, the answer seems to be "No". 

When you look at the list of known Go-related software projects on [Sensei's Library](https://senseis.xmp.net/?SGFFile), especially the libraries section, you will notice that there are indeed quite a few libraries. The problem is that all except one are written in non-C/C++ languages.

The exception is GNU Go, which is written in C, and which contains [a library component](http://www.gnu.org/software/gnugo/gnugo_16.html) that can read and write SGF files. The first problem is that the component is not a standalone library. The second and much more severe problem is that GNU Go is published under the GNU GPL license. Integrating the GNU Go code into a library would force the library to also adopt the GNU GPL license, which would prevent the library from being used in certain scenarios. Notably it would not be possible to integrate the library into an iOS app that is published on the Apple App Store - which unfortunately is exactly the main motivation behind this library project. If you want to read the FSF's stance on this check out their posts from 2010 [here](https://www.fsf.org/news/2010-05-app-store-compliance) and [here](https://www.fsf.org/blogs/licensing/more-about-the-app-store-gpl-enforcement).

There is also [Fuego](http://fuego.sourceforge.net/), which similar to GNU Go contains an SGF reading/writing component, but is published under the LGPL license. Although Fuego solves the license problem, there is still the other issue that the SGF-handling component is not built and distributed as a standalone library, but rather as part of a whole command line program.

At this point it seems clear that a new library project is in order. The question remains whether SGFC or Fuego should be adapted/wrapped. Here are some considerations:

- Fuego's SGF component is bound to the purpose of enabling Fuego, so there is a certain danger of limitations that serve that purpose. SGFC on the other hand is a standalone program without any obligations to a higher goal, and is therefore probably more general-purpose in nature.
- SGFC has a clear focus on robustness in the face of incomplete or even erroneous SGF data. When it can't handle a certain piece of data it has a documented mechanism of reporting warnings and/or errors to the user. This is a very valuable function for a library and not something that Fuego's SGF component can offer.
- SGFC can read files in older SGF formats and write them as FF[4], so it provides a valuable conversion function. While there are some hints in the Fuego source code that Fuego's SGF component can do a bit more than read only FF[4], there is certainly not the same amount of dedication to read old formats as there is in SGFC.

The conclusion from this miniature evaluation is that SGFC clearly seems to be the better choice.
