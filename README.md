# Project Title: Plant Disease Detection with Gemini LLM and Smart irigation system
#sumery for smart irrigation system: - 
The "Smart Irrigation System Using ESP32 & Blynk App" is an IoT-based project for automated irrigation. It utilizes ESP32, soil moisture and water level sensors, DHT11 sensor, relay module. The ESP32 connects to Blynk, enabling remote monitoring of soil conditions. The system activates the water pump based on soil moisture, temperature, and humidity. Automatic mode irrigates the field when moisture is low, while Manual mode allows manual control. The Blynk app displays real-time data on soil moisture, water level, and environmental conditions. The project is ideal for farms, and its video provides a concise overview of its functionality.

🔥Description:

This project demonstrates a plant disease detection application built using Gradio and the Gemini LLM. Users can upload images of plant leaves with potential diseases, and the application will leverage a pre-trained machine learning model to predict the disease. The Gemini LLM is then used to provide additional information and recommendations based on the predicted disease.

🔥Features:

Image upload: Users can upload images of plant leaves.
Disease prediction: A pre-trained machine learning model is used to predict the plant disease.
Additional information: The Gemini LLM provides context and recommendations related to the predicted disease.
User-friendly interface: The Gradio interface provides an intuitive way for users to interact with the application.

🥷🏻 Getting Started:

Clone the repository:

Bash
git clone https://github.com/your-username/AGRO-IOT.git


Install dependencies:

Bash
cd plant-disease-detection
pip install -r requirements.txt

Set up environment variables:

Create a .env file and add your API keys and other necessary environment variables:

GOOGLE_CLOUD_PROJECT=your_project_id
YOUR_API_KEY=your_api_key
Run the application:

Bash
python app.py
Outputs:

Disease prediction: The predicted disease name will be displayed.
Additional information: The Gemini LLM will provide relevant information about the predicted disease, including symptoms, causes, treatment options, and prevention strategies.
