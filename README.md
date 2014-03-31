hi-top
======

A project to investigate possibly interesting ttbar studies in
heavy-ion collisions.

TO DO
=====

- establish if Pythia8 provides decay times

      - Liliana: Pythia8 does not provide decay/production times/distances.
            Check in LilianasCode/results/pt0_En5TeV.root the decay/prod_time/position histograms (all entries are set to zero)

- understand the question of transverse v. longitudinal boost. Which
  is more relevant? What about the fact that the medium is moving
  v. top/W velocities (which are not speed of light)?

- implement a decoherence time that uses either 

    cos theta = (1-2m^2/E^2)

  or 

    cos theta = (1-2m^2/(pt^2+m^2))

  or even the actual theta between the W decay products (requires a
  bit more work).

     - Liliana: Done! (with actual theta between the W decay products)

- establish how well we can correlate kinematics with
  decay+decoherence time. This can be done just as a function of top
  and W pt. E.g. inclusive, pt>200, pt>300, pt>500. The question is
  going to be one of compromise between getting some spread in
  lifetimes and still having enough events for a measurement to be
  possible. It'll be fairly borderline for LHC, and probably OK for FCC.

     - Liliana: Check in LilianasCode/Images the Comparison files for LHC and FCC. It is shown the results for decay distance and decay distance + coherence time with different cuts for the minimum pt of the W boson. The upper plots represent the results using a transverse boost and the lower plots using a transverse + longitudinal boost. By increasing the pt cut, we are able to probe latter stages of the medium, altough the statistics for the LHC case, when pt > 500 GeV, is very low: from a total of 1Million events, only 400 survive... see LilianasCode/Images/Decay_ptW500_En100TeV.eps file
            Imposing a cut in the top will reduce even more this statistics.


- then move towards actual schematic analysis? And try to see how
  robust it is with background subtraction.


