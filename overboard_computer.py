import asyncio
import serial
import time
from winrt.windows.media.control import GlobalSystemMediaTransportControlsSessionManager as MediaManager

# --- Configuration ---
SERIAL_PORT = 'COM3'  # Update this to your device's actual COM port
BAUD_RATE = 115200
MAX_LENGTH = 127      # Matches (MAX_MESSAGE_LENGTH - 1) from your C++ code
POLL_INTERVAL = 1.0   # How often to check for song changes (in seconds)

async def get_current_media_info():
    """Fetches the currently playing song title and artist from Windows."""
    try:
        # Request access to the system media sessions
        sessions = await MediaManager.request_async()
        current_session = sessions.get_current_session()
        
        if current_session:
            # Try to grab the media properties asynchronously
            properties = await current_session.try_get_media_properties_async()
            if properties:
                title = properties.title
                artist = properties.artist
                
                # Format how you want it to appear on your display
                if title and artist:
                    return f"{title} - {artist}"
                elif title:
                    return title
        return None
    except Exception as e:
        # Occasional drops can happen if an app closes abruptly
        return None

def send_to_device(ser, track_name):
    """Truncates, packages, and sends the track info over serial."""
    if len(track_name) > MAX_LENGTH:
        track_name = track_name[:MAX_LENGTH]
        
    payload = f"{track_name}\n"
    try:
        ser.write(payload.encode('utf-8'))
        ser.flush()
        print(f"🎵 Now Displaying: {track_name}")
    except Exception as e:
        print(f"❌ Serial Error: {e}")

async def main():
    print(f"Connecting to device on {SERIAL_PORT}...")
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            print("✅ Connected! Monitoring Windows Media... (Press Ctrl+C to quit)")
            time.sleep(1) # Connection stability pause
            
            last_track = ""
            
            while True:
                # Fetch what Windows is currently playing
                current_track = await get_current_media_info()
                
                if current_track and current_track != last_track:
                    # Update the device only when a new song starts
                    send_to_device(ser, current_track)
                    last_track = current_track
                elif not current_track and last_track != "No Media Playing":
                    # Optional: Tell your device when nothing is playing anymore
                    send_to_device(ser, "No Media")
                    last_track = "No Media Playing"
                    
                # Wait before pulling media data again
                await asyncio.sleep(POLL_INTERVAL)
                
    except serial.SerialException:
        print(f"❌ Connection Failed. Is {SERIAL_PORT} plugged in or open elsewhere?")

if __name__ == "__main__":
    # Windows requires the asyncio loop to run to handle WinRT async calls
    asyncio.run(main())