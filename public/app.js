
document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('userForm');
    const userNameInput = document.getElementById('userName');
    const resultDiv = document.getElementById('result');

    form.addEventListener('submit', function (e) {
        e.preventDefault();
        const userName = userNameInput.value.trim();

        console.log('Submitting form for user:', userName); // Log when the form is submitted

        if (userName) {
            fetch('/check-privilege', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ userName: userName }),
            })
                .then(response => response.json())
                .then(data => {
                    console.log('Received response:', data.message); // Log received data
                    resultDiv.textContent = data.message;
                })
                .catch(error => {
                    console.error('Error:', error);
                    resultDiv.textContent = 'Error checking privilege';
                });
        } else {
            resultDiv.textContent = 'Please enter a user name.';
        }
    });
});
