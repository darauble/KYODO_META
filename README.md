# Kyodo News Metadata Editor

This is a useless application for all the people except me. Well, maybe there will be someone who would find it useful.

This is a part of personal [Kyodo News radio faxes collection](https://kyodonewsradiofax.wordpress.com/). It is designed
to manage titles for the posts on the site, add metadata to the image and help keep the track of increasing numbers.

Here's an example screenshot of this piece of software:

![Kyodo News Metadata Editor](screenshots/kyodo-meta-screenshot.png?raw=true)

C API is used for GTK+. To make this application nice and shiny GTKMM could be employed, but currently this porting is
out of scope.

# Building

This software is designed to run in Linux using GTK+ as GUI framework. In theory it could run on any platform which has
GTK+ support, but there's no plan to test that on my side.

Required libraries are GTK+3.0, JsonCpp and Exiv2.

Creade `build` directory, enter it, type `cmake ..`, then type `make` and that's it.

