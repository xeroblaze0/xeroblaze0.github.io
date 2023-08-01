---
layout: page
title: Using Baxter for Object Recognition and Manipulation
description: Embedded Systems Final Project
img: assets/baxter/terminator.gif
importance: 1
category: work
# related_publications: einstein1956investigations, einstein1950meaning
---

The goal for the project was to use Baxter to recognize a nerf gun, pick it up and fire it at a coffee mug. At each step Baxter asks the user for confirmation before moving to the next sequence in the task. [GitHub](https://github.com/ME495-EmbeddedSystems/final-project-terminator)<br>


### Overall System Architecture and High Level Concepts

We made Baxter a high level state machine to navigate the task. The state machine (commander node) coordinated his left arm, right arm, cameras, and image processing. We determined that the left arm would find, pick up, and aim the gun, and the right arm would pull the trigger. AprilTags were used to identify the inital position of the nerf gun using the cameras on Baxter's wrists.

<div class="img_row">
    <img class="col three" src="/assets/baxter/baxter_01.png">
</div>
<div class="col three caption">
    Baxter
</div>

We used the move_it kinematics library to manipulate both of Baxter's arms. Baxter's wrists/cameras presented a unique challenge because their rotation is not quite 360°, with the midpoint of the rotation placing the camera underneath the gripper. Since the his arm and camera would be in line with the nerf gun we wanted to use the wrist camera to aim (the only other options were his face camera and the camera on his other arm). Baxter also has a "safety bubble" that prevents the arms from colliding into the body. With the nerf gun in hand the trigger ended up falling into the safety bubble.

To get around these challenges we flipped the gun upside-down, then modeled and printed a riser to fit in the nerf gun's rail and a set of custom grippers. The riser did two things; it created a larger surface area for Baxter's grippers and raised the gun out of the camera's field of view. Without the riser and grippers the nerf gun occluded the camera nearly 50% including the target.

<div class="img_row">
    <img class="col three" src="/assets/baxter/baxter_02.png">
</div>
<div class="col three caption">
    Point of view from Baxter's wrist camera
</div>

Once Baxter had the nerf gun he looked for the target mug then aimed the nerf gun. The darknet_ros library was used for object recognition, with images fed from the wrist camera. Despite not having to train the classifier, darknet_ros was very slow running in real time, so aiming was the longest operation. The aiming task was deemed complete once the mug was in the middle of the camera's field of view.

While the riser did lift the trigger out of the safety bubble, Baxter's movement precision using the stock grippers was not enough the "thread the needle" in the space needed to pull the trigger. Swapping the stock grippers for the long ones resolved the issue, and when they were equipped with the rubber tips we were able to achieve a consistent trigger pull.

<div class="img_row">
    <img class="col three" src="/assets/baxter/terminator.gif">
</div>
<div class="col three caption">
    Dishing the Law
</div>

### Future Work

We would like to implement tracking and shooting of objects that move through space. This would require a more robust system than Darknet since the update rate was extremely slow. We could potentially also take out objects we aren't detecting in Darknet. For stationary objects, we could implement a planning algorithm that once the camera detects the desired object, we would no longer have to run Darknet or other object detection algorithms which would speed up the time it takes between first detecting an object and being lined up to shoot it.

[Here](https://youtu.be/2MRsNefNWmw) is a link to the final video showing Baxter in action.
