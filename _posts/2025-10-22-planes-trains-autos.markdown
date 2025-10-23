---
layout: post
title: Planes, Trains, and Automobiles
date: 2025-10-22
description: 
tags: API, python, GPT
thumbnail: /assets/pin/example1.jpg
---

An app to track all the things I see out the window

<div class="img_row">
    <img class="col three" src="/assets/tracker/screenhot.png">
</div>
<div class="caption">
    Downtown Chicago with transit overlay
</div>

### Chicago

Back again in Chicago, I'm in Uptown now off of Sheridan Rd. with a view of the lake and the approach lane for O'hare. I love being able to see the modals make the hustle of Chicago. I find myself on Flightradar24 and MarineTraffic often, and it's not great switching between tabs all the time, especially if Google Maps is also open. I endeavored to address that.

### Scope & Sources

I did some quick research and found that CTA offered an API. For flights I'd start with Flightradar24, and boats I'd start with MarineTracker. For the map I wanted a satelite view. I didn't know how I wanted to source a map, but I wanted a live feed if possible, and failing that, some aerial/satelite view.

I used Google colab notebooks to dial in the API. APIs have always been a pain point for me, the syntax and understanding the structure to receive the data just never percolated. Colab with Gemini really helped me through that. 

### CTA and the map

As I mentioned, Gemini in colab really turbo-charged my ability to parse through the response data, and it was then that I realized I actually had a different problem: how was I going to plot the data?

I spent a considerable amount of time (3 days) figuring this out and epxloring options. I initially started with geopandas and a shapefile of the neighborhoods of Chicago.

<div class="img_row">
    <img class="col three" src="/assets/tracker/shapefile_plot.png">
</div>

Voila! It's not perfect but it does plot the trains where trains ought to be. I used geopandas because I was already familiar with pandas and matplotlib. I learned about shapefiles and learned they likely weren't right for this application. Following the success of learning the CTA API, I searched for a similar service.

<div class="img_row">
    <img class="col three" src="/assets/tracker/arcgis.png">
</div>

<!-- <div class="caption">
    Shamelessly stolen, GrapheneOS doesn't allow screenshots of the lock screen
</div> -->

It was a matter of time before finding ArcGIS. It's a powerful suite that's able to provide a lot, especially with plugin support. For personal projects I strongly prefer to use Free and Open-Source Software. Enter Folium.

<div class="img_row">
    <img class="col three" src="/assets/tracker/folium_routes.png">
</div>

### Information

Playing around with Folium in Colab with Gemini was really working out and I was able to work out an aerial view. When I plotted the trains I later thought being able to see the routes would be a big UI improvement, and this is where the nature of the project finally revealed itself. I thought I was building what was merely a plotting app. Really, I was building a fetching, receiving, and amalgamzing app and my problem was sourcing the information. The CTA trains came from one source, the routes another, the stations another, the map another. I haven't even gotten to the planes or boats yet. I moved on anyway, cognizant that I might have to start optimizing for query requests

### And for madame, a prototype

<div class="img_row">
    <img class="col three" src="/assets/tracker/folium_trains.png">
</div>

After spending a rather awful long time debugging icons, I was able to create this masterpiece. Highlighting over a station shows its information in the tooltip. I settled for a simple dot rather than one with a letter in it (like you'd see at the station itself) due to the nature of the size constraints of the map at zoomed out scales. It isn't until you zoom in, where there's space to draw lines without overlap, that you're able to draw in more information. Given how I was going about this particular application, dynamically retireving the zoom level to draw the correct level of information wasn't feasible (or possible?).

Also compunding issues was the CSS nature of the icons. After trying to offset, I tried redrawing them scaled and proportioned to address the offset. Failing both of those, I found a CSS attribute and asked Gemini to walk me through it. Failing all three approaches I just asked Gemini how to address it; the initial approach with the offset was the right approach, but it suggested using different parameters to acheive the desired effect. After some back and forth, we were able to dial it in.

### Gemini

As I mentioned before, Gemini really turbo-charged how quickly and effectively I was able to test out and implement new ideas. Syntax was something that I struggled with. Maybe it's a dyslexic thing. But Gemini was able to insert code that worked and allowed me to continue rather unabatedly and focus on the real challenges that I wanted to address. 

I still have strong apprehensions and opinions on using GPT, especially in regards to hallucinating nonsense into the public domain, but in controlled and guided applications like this, there can be a lot of success.

That said, there was also a learning process to using it. In colab, it was almost an all or nothing approach. If it had generated some code, and I combed through making adjustments for the task at hand, the next bit of code generation would undo that. Likewise, it'd often get stuck going the same method of exectution, even when told explicitly otherwise. Refreshing the page, the only way I knew how to start a new chat with Gemini, solved that issue, but interrupted the workflow quite a bit. In VS Studio Code I found it much more capable and easier to work with.

### Final CTA Display

<div class="img_row">
    <img class="col three" src="/assets/tracker/final_cta2.png">
</div>

<div class="caption">
    Added layer control with Gemini
</div>

## Planes and Boats

Success with the CTA portion had me feeling confident, but that's where that ends. Turns out finding information is hard, let alone free information. And I suppose that makes sense. The CTA is a treasure in this regard.

Regarding flight data, I began with a source that looked promising from aviation stack. Again using Gemini to help parse API data, we drew what looked to be garbage. After quite a bit of trial and error and drawing more garbage (this is where I struggled with Gemini), we were able to work through it. The challenge here is that there is no real time information, only statuses of 'active', 'landed', 'scheduled', etc. Arrival and departure time would've needed to have been fetched elsewhere then matched, then interpolated in some fashion, and plotted in an informationally accurate way. In a typical use-case scenario, that would be fine, but I live on approach to O'Hare. It is hard to interpolate a flight path without affecting the take-off or descent. At O'Hare they queue landing planes over Lake Michigan. If I plotted planes coming in any which way, I'd miss what actually just flew over my head.

<div class="img_row">
    <img class="col three" src="/assets/tracker/plane.png">
</div>

<div class="caption">
    Airbus coming in from Mexico, pathed over Lake Michigan for queueing
</div>

Every source I checked required some sort of payment subscription for real-time data. A few sites have programs where they'll send you a free receiver and antenna to help build the network, or you can use your own and access premium features at discount. After doing research and going down the rabbit hole of RTL-SDR, I decided that this would *not* be another hardware project. With that, I scrapped adding plane information. With boats it was a similar story, but no data to test with.

