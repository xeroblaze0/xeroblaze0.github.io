---
layout: post
title: Design Principals for NHP Laboratory Animals
date: 2022-11-21
description: 
tags: CAD neuroscience 
thumbnail: 
---

## Naxos Labs

In collaboration with a veterinarian, we started a company that designed a range of toys specifically tailored for NHPs and other laboratory animals. Through our experience we developed guidelines derived from valuable lessons, observations, and notes gathered during our interactions with the animals. [Naxos Labs](https://naxoslab.ca/)

### Purposeful Minimal Design

<div class="row mt-3">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/monkey/img/01.png" class="img-fluid rounded z-depth-1" zoomable=true %}
    </div>
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/monkey/img/02.png" class="img-fluid rounded z-depth-1" zoomable=true %}
    </div>
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/monkey/img/03.png" class="img-fluid rounded z-depth-1" zoomable=true %}
    </div>
</div>

The toys were designed with simplicity in mind, featuring intentionally muted and minimized elements. The use of subtle patterns and the absence of any intricate details draw the eye's attention to outliers that serve as guides while using the toys, while the rounded corners and edges created a visually cohesive and gentle appearance. The goal was for the toys to be inviting and self-explanatory, with additional features and game rules revealed through play and exploration. 


<div class="img_row">
    <img class="col three" src="/assets/monkey/gif/00-2.gif">
</div>

Likewise, we also considered the time and labor constraints of the technicians and handlers who'd also work with the toys. To address this, we added intuitive quality of life features to make the toys more user-friendly and streamline their effort.

### Production Matters

We opted for the Prusa Mk3S 3D printers to manufacture the toys, enabling us to rapidly iterate on designs and materials. To enhance functionality, we upgraded the printers with 32-bit Raspberry Pi control boards and firmware, enabling remote printing, multi-printer management, and advanced control options. Additionally, we equipped the printers with tungsten coated heat breaks and nozzles which offer a heat-resistant and low-friction surface as a replacement for the typical PTFE tube.

We experimented with various materials and infills (PLA, PETG, TPU, wood, PC) but in the end landed on PLA. PETG was also on the brittle side for our use-case. ABS and ASA were contenders but PLA ended up being more compatible. PLA can be recycled, is (industrially) compostable, but ultimately won out because our vendor could verify that it was food-safe.  

### Future Ideas

Looking ahead there are several areas I would've like to have focused on. First, I would've developed a traceable QR code that'd be embossed on each toy. These QR codes will contain crucial traceability information such as material source, time of manufacture, batch history, satefy and material data sheets, etc. 

<div class="row mt-3">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/monkey/img/02_b.png" class="img-fluid rounded z-depth-1" %}
    </div>
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/monkey/img/01_b.png" class="img-fluid rounded z-depth-1" %}
    </div>
</div>

<div class="caption">
    Alternative designs for the toy underside
</div>

Additionally, I wanted to invest in in-house recycling capabilities. By leveraging our own recycling machines we would be able to efficiently recycle toys on an individual, colony, or as per needed. Laboratories would effectively reserve a certain amount of plastic that can be shaped, cleaned, and reshaped according to their unique requirements. By providing enhanced transparency and accountability from the very beginning we provide a solid foundation for current and future scientific, industrial, and eco-political (ie. controls on plastic production and use) needs.