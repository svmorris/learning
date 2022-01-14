import os
import time

teams = [
"germany",
"france",
"portugal",
"hungary"
    ]

time.sleep(3)


for i in teams:
    os.system(f'xdotool type "fn!live {i} stop"')
    os.system(f'xdotool key RETURN')
    time.sleep(1)

