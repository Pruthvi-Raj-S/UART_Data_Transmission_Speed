################################################################
#                       INCLUDES                               #
################################################################
import serial
import time
import tkinter as tk
from tkinter import scrolledtext, messagebox

# Global variables
ser = None  # Serial port object

# Data variables
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
data_bytes = None  # Encoded data to send
data_length = 0  # Length of data to send
chunk_size = 1  # Number of bytes to send in each chunk
total_bytes_sent = 0  # Total bytes sent
total_bytes_received = 0  # Total bytes received
received_data = b''  # Data received

# Timing variables
start_time_send = None
start_time_receive = None

# GUI setup
root = tk.Tk()
root.title("UART Communication")

# Define variables to hold transmission speeds, data lengths, and integrity check result
send_speed_var = tk.StringVar(value="Send Speed: N/A")
receive_speed_var = tk.StringVar(value="Receive Speed: N/A")
bytes_sent_var = tk.StringVar(value="Bytes Sent: 0")
bytes_received_var = tk.StringVar(value="Bytes Received: 0")
integrity_var = tk.StringVar(value="Data Integrity Check: N/A")

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

def start_transmission():
    global ser, data_bytes, data_length, total_bytes_sent, total_bytes_received, received_data
    global start_time_send

    # Serial port parameters
    port = 'COM7'  # Change this to your serial port
    baud_rate = 2400  # Adjust the baud rate as needed
    timeout = 0  # Non-blocking read

    # Reset variables
    total_bytes_sent = 0
    total_bytes_received = 0
    received_data = b''
    bytes_sent_var.set("Bytes Sent: 0")
    bytes_received_var.set("Bytes Received: 0")
    send_speed_var.set("Send Speed: N/A")
    receive_speed_var.set("Receive Speed: N/A")
    integrity_var.set("Data Integrity Check: N/A")
    sent_text.delete(1.0, tk.END)
    received_text.delete(1.0, tk.END)

    # Encode data
    data_bytes = data_to_send.encode('utf-8')
    data_length = len(data_bytes)

    # Open serial port
    try:
        ser = serial.Serial(port, baud_rate, timeout=timeout)
    except serial.SerialException as e:
        messagebox.showerror("Serial Port Error", f"Error opening serial port {port}:\n{e}")
        return

    # Allow time for serial port to initialize
    root.after(2000, start_sending)  # Wait 2 seconds before starting to send

def start_sending():
    global start_time_send
    start_time_send = time.perf_counter()
    send_data()

def send_data():
    global total_bytes_sent, data_bytes, data_length, start_time_send

    if total_bytes_sent < data_length:
        # Send next chunk
        chunk = data_bytes[total_bytes_sent:total_bytes_sent + chunk_size]
        try:
            bytes_written = ser.write(chunk)
        except serial.SerialException as e:
            messagebox.showerror("Serial Write Error", f"Error writing to serial port:\n{e}")
            ser.close()
            return

        if bytes_written > 0:
            total_bytes_sent += bytes_written
            # Update sent text and bytes sent
            sent_text_content = data_bytes[:total_bytes_sent].decode('utf-8', errors='replace')
            update_sent_text(sent_text_content)
            update_bytes_sent(total_bytes_sent)

            # Calculate send speed
            elapsed_time = time.perf_counter() - start_time_send
            if elapsed_time > 0:
                speed_send_bps = (total_bytes_sent * 10) / elapsed_time
                update_send_speed(speed_send_bps)

        # Schedule next send
        root.after(1, send_data)
    else:
        # Sending complete
        # Start receiving data
        start_receiving()

def start_receiving():
    global start_time_receive
    start_time_receive = time.perf_counter()
    receive_data()

def receive_data():
    global total_bytes_received, received_data, start_time_receive

    try:
        data = ser.read(1024)  # Read up to 1024 bytes
    except serial.SerialException as e:
        messagebox.showerror("Serial Read Error", f"Error reading from serial port:\n{e}")
        ser.close()
        return

    if data:
        received_data += data
        total_bytes_received += len(data)
        # Update received text and bytes received
        received_text_content = received_data.decode('utf-8', errors='replace')
        update_received_text(received_text_content)
        update_bytes_received(total_bytes_received)

        # Calculate receive speed
        elapsed_time = time.perf_counter() - start_time_receive
        if elapsed_time > 0:
            speed_receive_bps = (total_bytes_received * 10) / elapsed_time
            update_receive_speed(speed_receive_bps)

        # Check for end of message (null terminator)
        if b'\0' in data or "Error: Buffer Overflow\n" in received_text_content:
            # Reception complete
            ser.close()
            check_integrity()
            return

    # Schedule next read
    root.after(1, receive_data)

def check_integrity():
    # Data integrity check
    received_data_str = received_data.decode('utf-8', errors='replace').rstrip('\0')

    if received_data_str == "Error: Buffer Overflow\n":
        integrity_message = "Data Integrity Check: MCU rejected the data (Buffer Overflow)"
    elif received_data_str == data_to_send.rstrip('\0'):
        integrity_message = "Data Integrity Check: Success (Data matches)"
    else:
        mismatches = sum(1 for a, b in zip(data_to_send.rstrip('\0'), received_data_str) if a != b)
        integrity_message = f"Data Integrity Check: Failed ({mismatches} mismatched character(s))"

    update_integrity_check(integrity_message)

def update_send_speed(speed):
    send_speed_var.set(f"Send Speed: {speed:.2f} bits per second")

def update_receive_speed(speed):
    receive_speed_var.set(f"Receive Speed: {speed:.2f} bits per second")

def update_bytes_sent(count):
    bytes_sent_var.set(f"Bytes Sent: {count}")

def update_bytes_received(count):
    bytes_received_var.set(f"Bytes Received: {count}")

def update_integrity_check(message):
    integrity_var.set(message)

def update_sent_text(text):
    sent_text.delete(1.0, tk.END)
    sent_text.insert(tk.END, text)
    sent_text.see(tk.END)

def update_received_text(text):
    received_text.delete(1.0, tk.END)
    received_text.insert(tk.END, text)
    received_text.see(tk.END)

# Start the GUI event loop
root.mainloop()
