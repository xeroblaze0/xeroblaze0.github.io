---
layout: post
title: Shape Memory Alloy Actuation
description: Equilibrium Point Control 
date: 2020-03-17
img: /assets/sma/img01.jpg
thumbnail: /assets/sma/img01.jpg
importance: 1
# category: fun
tags: arduino control embedded-systems
# related_publications: einstein1956investigations, einstein1950meaning
---

The goal of this project was to explore the use of shape memory alloys to mimic human movement using equilibrium point control. [YouTube](https://youtu.be/f2VmKv2i89Y)

<!-- <p>
  <center>
    <a href="https://youtu.be/f2VmKv2i89Y"><img src="/portfolio/assets/img/winter_project/thumb.png" width="95%;" height="95%;"></a>
    <em> Demonstration video</em>
  </center>
</p> -->

### Shape Memory Alloys
Shape memory alloys (SMA) operate because of the unique crystalline structure of the alloy. The actuators used in this project are made with Nitinol, an SMA with a 1:1 Nickel-Titanium ratio. These alloys have a transition temperature and easily deform when below this temperature. The crystalline structure shifts but does not suffer permanent damage (C->A). Once the wire is heated above the transition temperature the crystals undergo a phase change and revert back to their original structure, with a large force (A->B). When the wire cools again the phase change reverses and the wire can be deformed again (B->C).

<p>
    <center><img src="/assets/sma/Figure_3-2.jpg" width="50%;" height="50%;" alt/>
    <br>
    <em>Diagram showing how SMAs atomic structure deforms</em></center>
</p>

As a wire, this deformation manifests as a change of length in the wire. For the actuators to actuate, a current is passed through the wire. The internal resistance of the wire heats it up above its transition temperature, instigating the phase change and *contraction* and creating a pulling force.

### Equilibrium Point Control
Equilibrium point control (EPC) is motor control through changing muscle stiffness. A 'reciprocal command' is sent to shift the equilibrium point, moving the limb. In the λ‐model of motor control, proposed by Feldman<sup>[[1]](https://www.ncbi.nlm.nih.gov/pubmed/15136283?dopt=Abstract)[[2]](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2342993/)</sup>, the reciprocal command, alters the relative activation of agonist and antagonist muscles to produce a shift in the equilibrium between the muscle force and external load. While it has fallen out of vogue in human motor control, this project explores using it as a means of actuation of SMAs.

<p>
    <center><img src="/assets/sma/alpha_model.png" width="100%;" height="100%;" alt/>
    <br>
    <em>α model: motor control through changing muscle stiffness</em></center>
</p>

### Actuator

The Miga T220 SMA linear actuator was chosen for this project. Other considerations included servo motors, magnetic actuators, belt/gear mechanical actuators, pneumatic systems, and other SMA actuators. Form, power, and hardware interface were the driving deciding factors. A decision matrix can be found [here](https://docs.google.com/spreadsheets/d/1p3fjq4K-Gl2H-Soi13WV8KOYeHxsrkHLGmXQxgn4opM/edit?usp=sharing)

<p>
    <center>
    <img src="/assets/sma/miga.jpg" width="70%;" height="70%;" alt/>
    <br>
    <em>Miga T220 SMA Linear Actuator</em>
    </center>
</p>

### Design and Fabrication

The project served as a study in rapid prototyping. I used Solidworks for part models, assembly, and drawings. The frame was built from acrylic cut from a laser cutter, special screws and couplings were printed using the Ultimaker3 3D printer. Plastic hardware bits are required for stacking the actuators, as the mounting holes are part of the circuit.

For the presentation at the Museum of Science and Industry, two (2) of the Miga actuators were removed and the fans repositioned to directly face the actuators. These changes allows faster actuation time at the cost of actuation force.

<p>
    <center><img src="/assets/sma/assembly.gif" width="50%;" height="50%;" alt/>
    <br>
    <em>Apparatus exploded view</em></center>
</p>

### Controller

See my [GitHub](https://github.com/alexanderhay2020/499) page.

### Discussion

The project as presented demonstrates an α-model method of motor control through changing the Nitinol wire properties. λ-model requires a feedback signal from the muscle spindle, a fiber running the length of the muscle that senses stretch sensory information. A λ-model could be modeled by installing a position sensor on the actuator or a rotary encoder at the joint, sending the muscle property data that the muscle spindle broadcasts. A PID controller could then be implemented to give the actuators a spring-like quality that is seen in muscle fibers<sup>[[3]](https://www.ncbi.nlm.nih.gov/pubmed/8930238)</sup>.

Future work would also involve building out the "forearm". For now the apparatus actuates a collar with a Base-15 u channel, seen with a bolt in place in the demo video.

<p>
  <center>
    <img src="/assets/sma/img01.jpg" width="80%;" height="80%;" alt/>
    <br>
    <em>Complete assembly of project</em>
  </center>
</p>


### References

 [1] Anatol G. Feldman (1986) Once More on the Equilibrium-Point Hypothesis (λ Model) for Motor Control, Journal of Motor Behavior, 18:1, 17-54, DOI: 10.1080/00222895.1986.10735369

 [2] Hinder, Mark R, and Theodore E Milner. “The case for an internal dynamics model versus equilibrium point control in human movement.” The Journal of physiology vol. 549,Pt 3 (2003): 953-63. doi:10.1113/jphysiol.2002.033845

 [3] Gribble PL, Ostry DJ. Origins of the power law relation between movement velocity and curvature: modeling the effects of muscle mechanics and limb dynamics. J Neurophysiol. 1996 Nov;76(5):2853-60. doi: 10.1152/jn.1996.76.5.2853. PubMed PMID: 8930238.