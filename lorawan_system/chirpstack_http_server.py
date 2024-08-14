from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/chirpstack', methods=['POST'])
def chirpstack_handler():
    # Get the JSON data sent by ChirpStack
    data = request.json
    print("Received data:", data)

    # Process the data as needed
    # For example, save it to a database or file

    # Respond to ChirpStack (optional)
    return jsonify({"status": "success"}), 200

if __name__ == '__main__':
    # Run the server on port 5050
    app.run(host='0.0.0.0', port=5050)