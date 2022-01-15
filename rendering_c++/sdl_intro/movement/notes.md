An important takeaway from this part is that calling the actual RenderPresent method is slow and should only be done once the entire frame is drawn out.

In practice this means that when moving an object on the screen, it is not good to call `clear_window` and then call `draw_circle`. In that case the window is overwritten followed by a call to `RenderPresent` then the new circle is drawn sepertly with its won `RenderPresent` call. This makes for a flashing ball as there is some time between the ball getting destroyed and the ball being redrawn.

The better way to do this is to clear out the original frame before drawing the ball, or calling all the draw methods and then doing `renderPresent` at the end. The later of these is implemented in main.c.

