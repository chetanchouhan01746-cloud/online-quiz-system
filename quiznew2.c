<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Online Quiz & Examination System</title>
    <style>
        body { font-family: Arial, sans-serif; background: #f4f6f9; display: flex; justify-content: center; padding: 20px; }
        .container { background: white; padding: 25px; border-radius: 10px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); width: 100%; max-width: 600px; }
        h1, h2 { text-align: center; color: #333; }
        input, select, button { width: 100%; padding: 10px; margin: 8px 0; border: 1px solid #ccc; border-radius: 5px; box-sizing: border-box; }
        button { background: #007bff; color: white; border: none; font-size: 16px; cursor: pointer; font-weight: bold; }
        button:hover { background: #0056b3; }
        .hidden { display: none; }
        .question-box { background: #f9f9f9; padding: 15px; border-left: 4px solid #007bff; margin-bottom: 15px; }
        .review-card { background: #f1f3f5; padding: 10px; margin: 8px 0; border-radius: 5px; }
    </style>
</head>
<body>
<div class="container">
    <h1>Online Quiz System</h1>

    <!-- STEP 1: CREATE QUIZ -->
    <div id="setup-section">
        <h2>Step 1: Create Custom Quiz</h2>
        <input type="text" id="q-text" placeholder="Type your question here...">
        <input type="text" id="opt-a" placeholder="Option A">
        <input type="text" id="opt-b" placeholder="Option B">
        <input type="text" id="opt-c" placeholder="Option C">
        <input type="text" id="opt-d" placeholder="Option D">
        <select id="correct-opt">
            <option value="">Select Correct Option</option>
            <option value="A">Option A</option>
            <option value="B">Option B</option>
            <option value="C">Option C</option>
            <option value="D">Option D</option>
        </select>
        <button onclick="addQuestion()">+ Add Question (<span id="q-count">0</span> added)</button>
        <button style="background:#28a745;" onclick="goToStudentLogin()">Finish & Start Exam</button>
    </div>

    <!-- STEP 2: STUDENT DETAILS -->
    <div id="login-section" class="hidden">
        <h2>Step 2: Student Registration</h2>
        <input type="text" id="student-name" placeholder="Enter Student Full Name">
        <input type="text" id="roll-no" placeholder="Enter Roll Number">
        <button onclick="startExam()">Start Exam</button>
    </div>

    <!-- STEP 3: TAKE EXAM -->
    <div id="exam-section" class="hidden">
        <h2 id="exam-header">Examination</h2>
        <div id="questions-container"></div>
        <button style="background:#28a745;" onclick="submitExam()">Submit Exam</button>
    </div>

    <!-- STEP 4: FINAL RESULT & ANSWER KEY -->
    <div id="result-section" class="hidden">
        <h2>Final Result</h2>
        <div id="score-summary" class="question-box"></div>
        <h3>Answer Key & Review</h3>
        <div id="review-container"></div>
        <button onclick="location.reload()">Create New Quiz</button>
    </div>
</div>

<script>
    let quiz = [];

    function addQuestion() {
        const q = document.getElementById('q-text').value;
        const a = document.getElementById('opt-a').value;
        const b = document.getElementById('opt-b').value;
        const c = document.getElementById('opt-c').value;
        const d = document.getElementById('opt-d').value;
        const correct = document.getElementById('correct-opt').value;

        if (!q || !a || !b || !c || !d || !correct) {
            alert("Please fill in all fields!");
            return;
        }
        quiz.push({ q, a, b, c, d, correct });
        document.getElementById('q-count').innerText = quiz.length;
        document.getElementById('q-text').value = "";
        document.getElementById('opt-a').value = "";
        document.getElementById('opt-b').value = "";
        document.getElementById('opt-c').value = "";
        document.getElementById('opt-d').value = "";
        document.getElementById('correct-opt').value = "";
    }

    function goToStudentLogin() {
        if (quiz.length === 0) { alert("Add at least 1 question first!"); return; }
        document.getElementById('setup-section').classList.add('hidden');
        document.getElementById('login-section').classList.remove('hidden');
    }

    function startExam() {
        const name = document.getElementById('student-name').value;
        const roll = document.getElementById('roll-no').value;
        if (!name || !roll) { alert("Enter your name and roll number!"); return; }

        document.getElementById('login-section').classList.add('hidden');
        document.getElementById('exam-section').classList.remove('hidden');

        const container = document.getElementById('questions-container');
        container.innerHTML = quiz.map((item, idx) => `
            <div class="question-box">
                <p><strong>Q${idx + 1}. ${item.q}</strong></p>
                <label><input type="radio" name="q${idx}" value="A" style="width:auto;"> A) ${item.a}</label><br>
                <label><input type="radio" name="q${idx}" value="B" style="width:auto;"> B) ${item.b}</label><br>
                <label><input type="radio" name="q${idx}" value="C" style="width:auto;"> C) ${item.c}</label><br>
                <label><input type="radio" name="q${idx}" value="D" style="width:auto;"> D) ${item.d}</label>
            </div>
        `).join('');
    }

    function submitExam() {
        let score = 0;
        let reviewHTML = "";

        quiz.forEach((item, idx) => {
            const selected = document.querySelector(`input[name="q${idx}"]:checked`);
            const userAns = selected ? selected.value : "Not Answered";
            if (userAns === item.correct) score++;

            reviewHTML += `
                <div class="review-card">
                    <strong>Q${idx + 1}. ${item.q}</strong><br>
                    Your Answer: <b>${userAns}</b> | Correct Answer: <b>${item.correct}</b>
                </div>
            `;
        });

        const percentage = ((score / quiz.length) * 100).toFixed(2);
        const status = percentage >= 40 ? "PASS" : "FAIL";

        document.getElementById('exam-section').classList.add('hidden');
        document.getElementById('result-section').classList.remove('hidden');
        document.getElementById('score-summary').innerHTML = `
            <p><strong>Student:</strong> ${document.getElementById('student-name').value}</p>
            <p><strong>Roll No:</strong> ${document.getElementById('roll-no').value}</p>
            <p><strong>Marks:</strong> ${score} / ${quiz.length} (${percentage}%)</p>
            <p><strong>Status:</strong> ${status}</p>
        `;
        document.getElementById('review-container').innerHTML = reviewHTML;
    }
</script>
</body>
</html>