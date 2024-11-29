################################################################
#                       INCLUDES                               
################################################################
import serial   #For UART Communication
import time     #For time functions
import tkinter as tk    #For GUI
from tkinter import scrolledtext, messagebox    #For GUI
import threading    #For running parallel process

################################################################
#                       Function Declaration                               
################################################################

################################################################
# \fn  		uart_communication()
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function communicates with UART
 ################################################################

def uart_communication():
    # Local Function and Initialization

    # Serial port parameters
    port = 'COM7'  # UART serial port
    baud_rate = 2400  # Baud rate
    timeout = 0  # Non-blocking read

    # Data to be sent
    data_to_send = (
            """Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting """
            """that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than """
            """taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending """
            """financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit """
            """targets and loan waivers, saying that they could be the sources of next banking crisis. Government """
            """should focus on sources of the next crisis, not just the last one. In particular, government should """
            """refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved """
            """by abandoning appropriate due diligence, creating the environment for future NPAs," Rajan said in the """
            """note. "Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more """
            """closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, """
            """is currently.""" + '\0'
        )
    
    # Open serial port
    ser = serial.Serial(port, baud_rate, timeout=timeout)

    # Allow some time for the serial port to initialize
    time.sleep(2)

    # Prepare variables for sending data
    total_bytes_sent = 0
    last_update_time_send = time.perf_counter()
    sample_interval_send = 0.5  # Interval in seconds to update the send speed
    bytes_sent_in_interval = 0

    # Convert data to bytes
    data_bytes = data_to_send.encode('utf-8')
    data_length = len(data_bytes)
    chunk_size = 1  # Send one byte at a time (adjust as needed)

    # Start sending data
    start_time_send = time.perf_counter()

    while total_bytes_sent < data_length:
        chunk = data_bytes[total_bytes_sent:total_bytes_sent + chunk_size]
        
        bytes_written = ser.write(chunk)

        if bytes_written > 0:
            total_bytes_sent += bytes_written
            bytes_sent_in_interval += bytes_written

            # Update sent text in GUI
            sent_text_content = data_bytes[:total_bytes_sent].decode('utf-8', errors='replace')
            root.after(0, lambda text=sent_text_content: update_sent_text(text))

            # Update total bytes sent in GUI
            root.after(0, lambda count=total_bytes_sent: update_bytes_sent(count))

            current_time_send = time.perf_counter()
            elapsed_time_send = current_time_send - last_update_time_send

            if elapsed_time_send >= sample_interval_send:
                # Calculate send speed
                speed_send_bps = (bytes_sent_in_interval * 10) / elapsed_time_send
                root.after(0, lambda s=speed_send_bps: update_send_speed(s))
                # Reset counters
                last_update_time_send = current_time_send
                bytes_sent_in_interval = 0
        else:
            # No data sent, small delay to prevent high CPU usage
            time.sleep(0.01)

    end_time_send = time.perf_counter()
    total_time_send = end_time_send - start_time_send

    # Final update of send speed and bytes sent
    if total_time_send > 0:
        overall_speed_send_bps = (total_bytes_sent * 10) / total_time_send
        root.after(0, lambda s=overall_speed_send_bps: update_send_speed(s))
        root.after(0, lambda count=total_bytes_sent: update_bytes_sent(count))

    # Prepare to receive data
    received_data = b''
    total_bytes_received = 0
    last_update_time_receive = time.perf_counter()
    sample_interval_receive = 0.5  # Interval in seconds to update the receive speed
    bytes_received_in_interval = 0

    # Start receiving data
    expected_bytes = data_length
    start_time_receive = time.perf_counter()

    while total_bytes_received < expected_bytes:
        data = ser.read(expected_bytes - total_bytes_received)

        if data:
            received_data += data
            bytes_received = len(data)
            total_bytes_received += bytes_received
            bytes_received_in_interval += bytes_received

            # Update received text in GUI
            received_text_content = received_data.decode('utf-8', errors='replace')
            root.after(0, lambda text=received_text_content: update_received_text(text))

            # Update total bytes received in GUI
            root.after(0, lambda count=total_bytes_received: update_bytes_received(count))

            current_time_receive = time.perf_counter()
            elapsed_time_receive = current_time_receive - last_update_time_receive

            if elapsed_time_receive >= sample_interval_receive:
                # Calculate receive speed
                speed_receive_bps = (bytes_received_in_interval * 10) / elapsed_time_receive
                root.after(0, lambda s=speed_receive_bps: update_receive_speed(s))
                # Reset counters
                last_update_time_receive = current_time_receive
                bytes_received_in_interval = 0
        else:
            # No data received, small delay to prevent high CPU usage
            time.sleep(0.01)

    end_time_receive = time.perf_counter()
    total_time_receive = end_time_receive - start_time_receive

    # Final update of receive speed and bytes received
    if total_time_receive > 0:
        overall_speed_receive_bps = (total_bytes_received * 10) / total_time_receive
        root.after(0, lambda s=overall_speed_receive_bps: update_receive_speed(s))
        root.after(0, lambda count=total_bytes_received: update_bytes_received(count))

    # Close serial port
    ser.close()

    # Check data integrity
    sent_data_str = data_bytes.decode('utf-8', errors='replace')
    received_data_str = received_data.decode('utf-8', errors='replace')

    if received_data_str == "Error: Buffer Overflow\n":
        integrity_message = "Data Integrity Check: MCU rejected the data (Buffer Overflow)"
    elif received_data_str.rstrip('\0') == data_to_send.rstrip('\0'):
        integrity_message = "Data Integrity Check: Success (Data matches)"
    else:
        mismatches = sum(1 for a, b in zip(data_to_send.rstrip('\0'), received_data_str) if a != b)
        integrity_message = f"Data Integrity Check: Failed ({mismatches} mismatched character(s))"

    # Update integrity check result in GUI
    root.after(0, lambda msg=integrity_message: update_integrity_check(msg))

######################################################################
# \fn  		start_transmission()
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function runs when Start transmission is clicked
 ######################################################################
def start_transmission():
    # Start UART communication in a separate thread
    threading.Thread(target=uart_communication, daemon=True).start()

######################################################################
# \fn  		update_send_speed(speed)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updated the send speed on GUI
 ######################################################################
def update_send_speed(speed):
    send_speed_var.set(f"Send Speed: {speed:.2f} bits per second")

######################################################################
# \fn  		update_receive_speed(speed)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updated the receive speed on GUI
 ######################################################################
def update_receive_speed(speed):
    receive_speed_var.set(f"Receive Speed: {speed:.2f} bits per second")

######################################################################
# \fn  		update_bytes_sent(count)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updated the bytes sent on GUI
######################################################################
def update_bytes_sent(count):
    bytes_sent_var.set(f"Bytes Sent: {count}")

######################################################################
# \fn  		update_bytes_received(count)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updated the bytes received on GUI
######################################################################
def update_bytes_received(count):
    bytes_received_var.set(f"Bytes Received: {count}")

######################################################################
# \fn  		update_integrity_check(message)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updateds the data integrity on GUI
######################################################################
def update_integrity_check(message):
    integrity_var.set(message)

######################################################################
# \fn  		update_sent_text(text)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updateds the texts thats been sent on GUI
######################################################################
def update_sent_text(text):
    sent_text.delete(1.0, tk.END)  # Clear previous content
    sent_text.insert(tk.END, text)
    sent_text.see(tk.END)  # Scroll to the end

######################################################################
# \fn  		update_received_text(text)
# \brief
# 
# \details
# 
# \param       none
# \return      none
# \remarks     This function updateds the texts thats been received on GUI
######################################################################
def update_received_text(text):
    received_text.delete(1.0, tk.END)  # Clear previous content
    received_text.insert(tk.END, text)
    received_text.see(tk.END)  # Scroll to the end

# Set up GUI
root = tk.Tk()
root.title("UART Communication")

# Define variables to hold transmission speeds, data lengths, and integrity check result
send_speed_var = tk.StringVar()
receive_speed_var = tk.StringVar()
bytes_sent_var = tk.StringVar()
bytes_received_var = tk.StringVar()
integrity_var = tk.StringVar()
send_speed_var.set("Send Speed: N/A")
receive_speed_var.set("Receive Speed: N/A")
bytes_sent_var.set("Bytes Sent: 0")
bytes_received_var.set("Bytes Received: 0")
integrity_var.set("Data Integrity Check: N/A")

# Create GUI elements
start_button = tk.Button(root, text="Start Transmission", command=start_transmission)
send_speed_label = tk.Label(root, textvariable=send_speed_var)
bytes_sent_label = tk.Label(root, textvariable=bytes_sent_var)
receive_speed_label = tk.Label(root, textvariable=receive_speed_var)
bytes_received_label = tk.Label(root, textvariable=bytes_received_var)
integrity_label = tk.Label(root, textvariable=integrity_var, fg="blue")

sent_label = tk.Label(root, text="Data Sent:")
sent_text = scrolledtext.ScrolledText(root, width=60, height=10)
received_label = tk.Label(root, text="Data Received:")
received_text = scrolledtext.ScrolledText(root, width=60, height=10)

# Layout the widgets using grid
start_button.grid(row=0, column=0, columnspan=2, pady=10)
send_speed_label.grid(row=1, column=0, sticky='w', padx=10)
receive_speed_label.grid(row=1, column=1, sticky='w', padx=10)
bytes_sent_label.grid(row=2, column=0, sticky='w', padx=10)
bytes_received_label.grid(row=2, column=1, sticky='w', padx=10)
integrity_label.grid(row=3, column=0, columnspan=2, pady=5)
sent_label.grid(row=4, column=0, sticky='w', padx=10)
received_label.grid(row=4, column=1, sticky='w', padx=10)
sent_text.grid(row=5, column=0, padx=10, pady=5)
received_text.grid(row=5, column=1, padx=10, pady=5)

# Start the GUI event loop
root.mainloop()
