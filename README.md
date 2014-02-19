hi-top
======

A project to investigate possibly interesting ttbar studies in
heavy-ion collisions.

TO DO
=====

- establish if Pythia8 provides decay times

- understand the question of transverse v. longitudinal boost. Which
  is more relevant? What about the fact that the medium is moving
  v. top/W velocities (which are not speed of light)?

- implement a decoherence time that uses either 

    cos theta = (1-2m^2/E^2)

  or 

    cos theta = (1-2m^2/(pt^2+m^2))

  or even the actual theta between the W decay products (requires a
  bit more work).

- establish how well we can correlate kinematics with
  decay+decoherence time. This can be done just as a function of top
  and W pt. E.g. inclusive, pt>200, pt>300, pt>500. The question is
  going to be one of compromise between getting some spread in
  lifetimes and still having enough events for a measurement to be
  possible. It'll be fairly borderline for LHC, and probably OK for FCC.


- then move towards actual schematic analysis? And try to see how
  robust it is with background subtraction.


