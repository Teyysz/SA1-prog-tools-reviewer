<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Programming Tools Reviewer</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
  :root{
    --bg:#0d1117;
    --panel:#131a24;
    --panel-2:#171f2c;
    --line:#25313f;
    --text:#dbe4ee;
    --dim:#7c8a9c;
    --accent:#39d98a;
    --accent-dim:#1f6b48;
    --bad:#ff6b6b;
    --bad-dim:#5c2626;
    --amber:#f0b64c;
    --mono: 'IBM Plex Mono', ui-monospace, SFMono-Regular, Menlo, Consolas, monospace;
    --sans: 'IBM Plex Sans', -apple-system, Segoe UI, Roboto, sans-serif;
  }
  *{box-sizing:border-box;}
  html,body{margin:0;height:100%;}
  body{
    background:
      radial-gradient(1200px 600px at 85% -10%, rgba(57,217,138,0.06), transparent 60%),
      var(--bg);
    color:var(--text);
    font-family:var(--sans);
    display:flex;
    min-height:100vh;
  }
  ::selection{background:var(--accent-dim);}

  #sidebar{
    width:270px; flex:0 0 270px;
    background:var(--panel);
    border-right:1px solid var(--line);
    padding:20px 16px 16px;
    display:flex; flex-direction:column; gap:14px;
    position:sticky; top:0; height:100vh; overflow-y:auto;
  }
  .brand{font-family:var(--mono); font-size:12px; letter-spacing:.12em; color:var(--accent); text-transform:uppercase;}
  .brand-sub{font-size:18px; font-weight:600; line-height:1.25; margin-top:4px;}
  .prompt-line{font-family:var(--mono); font-size:12px; color:var(--dim); display:flex; gap:6px; align-items:center;}
  .prompt-line .caret{color:var(--accent); animation:blink 1.1s step-end infinite;}
  @keyframes blink{ 50%{opacity:0;} }

  #quizSelectWrap{display:flex; flex-direction:column; gap:4px;}
  #quizSelectWrap label{font-family:var(--mono); font-size:11px; color:var(--dim); text-transform:uppercase; letter-spacing:.06em;}
  select#quizSelect{
    background:#0a0f16; color:var(--text); border:1px solid var(--line);
    border-radius:6px; padding:9px 10px; font-family:var(--mono); font-size:13px;
  }

  #progressWrap{background:var(--panel-2); border:1px solid var(--line); border-radius:8px; padding:10px 12px; font-family:var(--mono); font-size:12px;}
  #progressBarOuter{height:6px; background:#0a0f16; border-radius:4px; overflow:hidden; margin-top:8px; border:1px solid var(--line);}
  #progressBarInner{height:100%; width:0%; background:linear-gradient(90deg,var(--accent-dim),var(--accent)); transition:width .25s ease;}

  #navGrid{display:grid; grid-template-columns:repeat(5,1fr); gap:6px; overflow-y:auto;}
  .navBtn{
    aspect-ratio:1/1; border:1px solid var(--line); background:var(--panel-2); color:var(--dim);
    font-family:var(--mono); font-size:12px; border-radius:6px;
    display:flex; align-items:center; justify-content:center; cursor:pointer;
    transition:all .15s ease;
  }
  .navBtn:hover{border-color:var(--accent); color:var(--text);}
  .navBtn.answered{background:rgba(57,217,138,0.1); color:var(--accent); border-color:var(--accent-dim);}
  .navBtn.current{outline:2px solid var(--accent); outline-offset:1px;}
  .navBtn.correct{background:rgba(57,217,138,0.18); color:var(--accent); border-color:var(--accent);}
  .navBtn.incorrect{background:rgba(255,107,107,0.15); color:var(--bad); border-color:var(--bad);}

  #finishBtn{
    margin-top:auto; background:var(--accent); color:#0a1510; border:none;
    font-family:var(--mono); font-weight:700; font-size:13px; letter-spacing:.03em;
    padding:12px; border-radius:8px; cursor:pointer; text-transform:uppercase;
  }
  #finishBtn:hover{filter:brightness(1.08);}

  #main{flex:1; padding:36px 48px 80px; max-width:900px; margin:0 auto;}
  .qMeta{font-family:var(--mono); font-size:12px; color:var(--dim); display:flex; justify-content:space-between; margin-bottom:10px;}
  .qMeta .tag{color:var(--amber); border:1px solid var(--line); padding:2px 8px; border-radius:20px;}
  .qStem{font-size:17px; line-height:1.6; white-space:pre-wrap; margin-bottom:14px;}
  pre.code{
    background:#0a0f16; border:1px solid var(--line); border-left:3px solid var(--accent-dim);
    border-radius:6px; padding:16px 18px; font-family:var(--mono); font-size:13.5px;
    line-height:1.55; overflow-x:auto; color:#b9e6cd; margin:0 0 18px;
  }
  .hint{font-family:var(--mono); font-size:11.5px; color:var(--dim); margin:-6px 0 14px;}
  .flagNote{
    font-family:var(--mono); font-size:11.5px; color:var(--amber);
    background:rgba(240,182,76,0.08); border:1px solid rgba(240,182,76,0.3);
    border-radius:6px; padding:8px 10px; margin:-6px 0 14px;
  }

  .choiceList{display:flex; flex-direction:column; gap:8px; margin-bottom:8px;}
  .choice{
    display:flex; gap:12px; align-items:flex-start; background:var(--panel);
    border:1px solid var(--line); border-radius:8px; padding:12px 14px; cursor:pointer;
    transition:border-color .15s ease, background .15s ease;
  }
  .choice:hover{border-color:var(--accent-dim);}
  .choice input{margin-top:3px; accent-color:var(--accent);}
  .choice .txt{white-space:pre-wrap; font-size:14.5px; line-height:1.5;}
  .choice.selected{border-color:var(--accent); background:rgba(57,217,138,0.06);}
  .choice.showCorrect{border-color:var(--accent); background:rgba(57,217,138,0.14);}
  .choice.showWrong{border-color:var(--bad); background:rgba(255,107,107,0.1);}

  #feedbackBox{margin-top:16px; padding:12px 14px; border-radius:8px; font-family:var(--mono); font-size:13px; display:none;}
  #feedbackBox.ok{display:block; background:rgba(57,217,138,0.1); border:1px solid var(--accent-dim); color:var(--accent);}
  #feedbackBox.bad{display:block; background:rgba(255,107,107,0.08); border:1px solid var(--bad-dim); color:var(--bad);}

  .navRow{display:flex; justify-content:space-between; margin-top:28px; gap:12px;}
  .navRow button{
    font-family:var(--mono); font-size:13px; padding:11px 20px; border-radius:8px;
    border:1px solid var(--line); background:var(--panel-2); color:var(--text); cursor:pointer;
  }
  .navRow button:hover{border-color:var(--accent);}
  .navRow button:disabled{opacity:.35; cursor:not-allowed;}

  #resultsScreen{display:none;}
  .scoreCard{
    text-align:center; background:var(--panel); border:1px solid var(--line);
    border-radius:14px; padding:48px 32px; margin-bottom:24px;
  }
  .scoreCard .big{font-family:var(--mono); font-size:64px; font-weight:700; color:var(--accent);}
  .scoreCard .sub{color:var(--dim); font-family:var(--mono); font-size:13px; margin-top:6px;}
  .resultsGrid{display:grid; grid-template-columns:repeat(10,1fr); gap:6px; margin-bottom:28px;}
  .rBox{
    aspect-ratio:1/1; border-radius:5px; font-family:var(--mono); font-size:11px;
    display:flex; align-items:center; justify-content:center; cursor:pointer; border:1px solid var(--line);
  }
  .rBox.correct{background:rgba(57,217,138,0.18); color:var(--accent); border-color:var(--accent);}
  .rBox.incorrect{background:rgba(255,107,107,0.15); color:var(--bad); border-color:var(--bad);}
  .actionsRow{display:flex; gap:12px; justify-content:center;}
  .actionsRow button{
    font-family:var(--mono); font-size:13px; padding:12px 22px; border-radius:8px;
    border:1px solid var(--line); background:var(--panel-2); color:var(--text); cursor:pointer;
  }
  .actionsRow button.primary{background:var(--accent); color:#0a1510; border:none; font-weight:700;}

  @media(max-width:820px){
    body{flex-direction:column;}
    #sidebar{position:relative; width:100%; height:auto; flex:none;}
    #navGrid{max-height:180px;}
    #main{padding:24px 18px 60px;}
    .resultsGrid{grid-template-columns:repeat(6,1fr);}
  }
</style>
</head>
<body>

<div id="sidebar">
  <div>
    <div class="brand">// programming_tools.py</div>
    <div class="brand-sub" id="brandTitle">Programming Tools Reviewer</div>
  </div>
  <div class="prompt-line"><span id="loadedCount">0</span> questions loaded<span class="caret">_</span></div>

  <div id="quizSelectWrap">
    <label for="quizSelect">Active Quiz</label>
    <select id="quizSelect"></select>
  </div>

  <div id="progressWrap">
    <div style="display:flex;justify-content:space-between;">
      <span>ANSWERED</span><span id="progressText">0 / 0</span>
    </div>
    <div id="progressBarOuter"><div id="progressBarInner"></div></div>
  </div>

  <div id="navGrid"></div>

  <button id="finishBtn">Grade Quiz ▸</button>
</div>

<div id="main">

  <div id="quizScreen">
    <div class="qMeta">
      <span id="qCounter">Question 1 / 10</span>
      <span class="tag" id="qTypeTag">SINGLE</span>
    </div>

    <div class="qStem" id="qStem"></div>
    <pre class="code" id="qCode" style="display:none;"></pre>
    <div id="qFlag" class="flagNote" style="display:none;"></div>
    <div id="qBody"></div>
    <div id="feedbackBox"></div>

    <div class="navRow">
      <button id="prevBtn">◂ Previous</button>
      <button id="nextBtn">Next ▸</button>
    </div>
  </div>

  <div id="resultsScreen">
    <div class="scoreCard">
      <div class="big" id="scoreBig">0%</div>
      <div class="sub" id="scoreSub">0 of 0 correct</div>
    </div>
    <div class="resultsGrid" id="resultsGrid"></div>
    <div class="actionsRow">
      <button class="primary" id="reviewWrongBtn">Review Missed Questions</button>
      <button id="retakeBtn">Retake Quiz</button>
    </div>
  </div>

</div>

<script>
/* =========================================================
   QUESTION DATA — Programming Tools Reviewer
   (checked for duplicate questions across all sets — none found)
========================================================= */
const QUIZZES = {

"1732168": {
  title: "Quiz 1732168 — IDEs & VS Code Tools",
  questions: [
{q:1,type:"single",stem:"Debuggers allow developers to step through code line by line to find errors.",
 opts:[["A","True"],["B","False"]], ans:"A"},

{q:2,type:"single",stem:"Which VS Code feature helps programmers by suggesting code completions?",
 opts:[["A","Debugger"],["B","Breakpoints"],["C","Snippets"],["D","IntelliSense"]], ans:"D"},

{q:3,type:"single",stem:"All IDEs come with built-in version control and API testing features.",
 opts:[["A","False"],["B","True"]], ans:"A"},

{q:4,type:"single",stem:"Which programming tool helps enforce coding standards automatically?",
 opts:[["A","Debugger"],["B","Compiler"],["C","Interpreter"],["D","Prettier"]], ans:"D"},

{q:5,type:"single",stem:"Breakpoints in an IDE are used for:",
 opts:[["A","Formatting code automatically"],["B","Improving code readability"],
       ["C","Running code without compiling"],["D","Pausing program execution during debugging"]], ans:"D"},

{q:6,type:"single",stem:"What is the primary purpose of an IDE?",
 opts:[["A","To manage cloud deployments"],["B","To replace version control tools like Git"],
       ["C","To compile code only"],
       ["D","To provide a complete environment for writing, testing, and debugging programs"]], ans:"D"},

{q:7,type:"single",stem:"The Prettier extension is mainly used for:",
 opts:[["A","Managing Git repositories"],["B","Running live servers"],
       ["C","Code formatting"],["D","Debugging JavaScript"]], ans:"C"},

{q:8,type:"single",stem:"Which of the following is NOT a feature of an Integrated Development Environment (IDE)?",
 opts:[["A","Version control system"],["B","Code editor"],
       ["C","Debugger"],["D","File explorer"]], ans:"A"},

{q:9,type:"single",stem:"If a developer wants to run and preview a web page instantly inside VS Code, which extension is best?",
 opts:[["A","Prettier"],["B","REST Client"],["C","Docker"],["D","Live Server"]], ans:"D"},

{q:10,type:"single",stem:"An IDE combines editing, debugging, and project management tools in one application.",
 opts:[["A","True"],["B","False"]], ans:"A"},

{q:11,type:"single",stem:"A linter is a tool used to optimize program performance.",
 opts:[["A","False"],["B","True"]], ans:"A"},

{q:12,type:"single",stem:"Which extension allows you to automatically check and fix JavaScript/TypeScript code style issues?",
 opts:[["A","Prettier"],["B","Docker"],["C","ESLint"],["D","GitLens"]], ans:"C"},

{q:13,type:"single",stem:"Extensions in VS Code can add features such as syntax highlighting, linting, or language support.",
 opts:[["A","True"],["B","False"]], ans:"A"}
  ]
},

"1732178": {
  title: "Quiz 1732178 — Coding Standards & Conventions",
  questions: [
{q:1,type:"single",stem:"What is the main difference between coding standards and coding conventions?",
 opts:[["A","Conventions apply only to one programming language, standards apply to all"],
       ["B","Standards are required rules, while conventions are more like guidelines"],
       ["C","Standards are for beginners, conventions are for experts"],
       ["D","Standards are optional, while conventions are mandatory"]], ans:"B"},

{q:2,type:"single",stem:"Coding conventions are strict rules that must always be followed without exception.",
 opts:[["A","True"],["B","False"]], ans:"B"},

{q:3,type:"single",stem:"Which of the following is an example of a coding convention?",
 opts:[["A","Running unit tests on each commit"],["B","Writing a project README file"],
       ["C","Always writing comments in uppercase letters"],
       ["D","Using camelCase for variable names in JavaScript"]], ans:"D"},

{q:4,type:"single",stem:"A benefit of using software development tools is:",
 opts:[["A","Improved productivity and efficiency"],["B","More manual work for the programmer"],
       ["C","Reduced collaboration among developers"],["D","Increased errors in code"]], ans:"A"},

{q:5,type:"single",stem:"Coding standards make it easier to maintain software over time.",
 opts:[["A","True"],["B","False"]], ans:"A"},

{q:6,type:"single",stem:"A debugger is a tool that helps programmers step through code to identify errors.",
 opts:[["A","False"],["B","True"]], ans:"B"},

{q:7,type:"single",stem:"Photoshop is a tool commonly used to help maintain coding standards automatically?",
 opts:[["A","False"],["B","True"]], ans:"A"},

{q:8,type:"single",stem:"Which of the following is NOT considered a software development tool?",
 opts:[["A","Integrated Development Environment (IDE)"],["B","Version Control System"],
       ["C","Waterfall Model"],["D","Debugger"]], ans:"C"},

{q:9,type:"single",stem:"Coding standards are important because they:",
 opts:[["A","Automatically fix all bugs"],
       ["B","Help maintain code readability, consistency, and quality"],
       ["C","Ensure every developer uses the same programming language"],
       ["D","Eliminate the need for testing"]], ans:"B"},

{q:10,type:"single",stem:"Which statement about coding standards is TRUE?",
 opts:[["A","They remove the need for debugging"],["B","They are only useful for large organizations"],
       ["C","They automatically optimize program performance"],
       ["D","They make it easier for teams to collaborate on projects"]], ans:"D"},

{q:11,type:"single",stem:"Which of the following best describes a coding standard?",
 opts:[["A","A personal style preference of the programmer"],
       ["B","A set of agreed-upon rules for writing consistent, maintainable code"],
       ["C","A debugging process to find and fix errors"],
       ["D","A tool that automatically generates code"]], ans:"B"},

{q:12,type:"single",stem:"Without development tools, programmers can still write code but may lose productivity and efficiency.",
 opts:[["A","False"],["B","True"]], ans:"B"},

{q:13,type:"single",stem:"Using consistent naming conventions makes programs easier for others to read.",
 opts:[["A","False"],["B","True"]], ans:"B"},

{q:14,type:"single",stem:"Why are coding standards important in team projects?",
 opts:[["A","They automatically fix all bugs in a program"],["B","They make code run faster"],
       ["C","They ensure that all developers write code in a consistent and understandable way"],
       ["D","They replace the need for testing"]], ans:"C"},

{q:15,type:"single",stem:"Software development tools are only used by expert programmers.",
 opts:[["A","False"],["B","True"]], ans:"A"}
  ]
},

"clean-architecture": {
  title: "Clean Architecture",
  questions: [
{q:1,type:"single",stem:"What is Clean Architecture?",
 opts:[["A","A UI design framework for building responsive websites"],
       ["B","A software design approach that emphasizes separation of concerns, maintainability, and testability"],
       ["C","A database management system for cloud applications"],
       ["D","A testing framework exclusive to Java applications"]], ans:"B"},

{q:2,type:"single",stem:"Which of the following is a benefit of using Clean Architecture?",
 opts:[["A","It eliminates the need for testing"],["B","It improves maintainability and scalability"],
       ["C","It requires a specific programming language"],["D","It increases coupling between components"]], ans:"B"},

{q:3,type:"single",stem:"Clean Architecture makes code testable without dependency on which two components?",
 opts:[["A","Version control and debugging tools"],["B","UI and database"],
       ["C","Compilers and interpreters"],["D","APIs and servers"]], ans:"B"},

{q:4,type:"single",stem:"What does Clean Architecture support in terms of frameworks and tools?",
 opts:[["A","Locking the project into one framework permanently"],
       ["B","Flexible replacement of frameworks and tools"],
       ["C","Removing the need for any framework"],["D","Using only proprietary tools"]], ans:"B"},

{q:5,type:"single",stem:"Which principle does Clean Architecture emphasize?",
 opts:[["A","Tight coupling between UI and business logic"],["B","Separation of concerns"],
       ["C","Mixing all logic into a single layer"],["D","Ignoring maintainability for faster development"]], ans:"B"}
  ]
}

};

/* =========================================================
   APP LOGIC
========================================================= */
let activeQuizId = Object.keys(QUIZZES)[0];
let Q = QUIZZES[activeQuizId].questions;
let TOTAL = Q.length;
let current = 0;
let answers = {};
let graded = false;
let gradeResults = {};

const navGrid = document.getElementById('navGrid');
const progressText = document.getElementById('progressText');
const progressBarInner = document.getElementById('progressBarInner');
const quizSelect = document.getElementById('quizSelect');
const brandTitle = document.getElementById('brandTitle');
const loadedCount = document.getElementById('loadedCount');

function populateQuizSelect(){
  quizSelect.innerHTML = '';
  Object.keys(QUIZZES).forEach(id=>{
    const o = document.createElement('option');
    o.value = id; o.textContent = QUIZZES[id].title;
    quizSelect.appendChild(o);
  });
  quizSelect.value = activeQuizId;
}
populateQuizSelect();

quizSelect.onchange = ()=>{
  loadQuiz(quizSelect.value);
};

function loadQuiz(id){
  activeQuizId = id;
  Q = QUIZZES[id].questions;
  TOTAL = Q.length;
  current = 0;
  answers = {};
  graded = false;
  gradeResults = {};
  document.getElementById('main').scrollTop = 0;
  loadedCount.textContent = TOTAL;
  document.getElementById('resultsScreen').style.display='none';
  document.getElementById('quizScreen').style.display='block';
  document.getElementById('sidebar').style.display='flex';
  buildNav();
  render();
}

function buildNav(){
  navGrid.innerHTML = '';
  Q.forEach((qq,i)=>{
    const b = document.createElement('div');
    b.className = 'navBtn';
    b.textContent = qq.q;
    b.onclick = ()=>{ current = i; render(); };
    navGrid.appendChild(b);
  });
}

function isAnswered(q){
  const a = answers[q.q];
  if(a===undefined) return false;
  if(q.type==='single') return !!a;
  if(q.type==='multi') return a && a.length>0;
  return false;
}

function updateProgress(){
  const answeredCount = Q.filter(isAnswered).length;
  progressText.textContent = answeredCount + ' / ' + TOTAL;
  progressBarInner.style.width = (answeredCount/TOTAL*100) + '%';
  const btns = navGrid.children;
  Q.forEach((qq,i)=>{
    btns[i].classList.toggle('answered', isAnswered(qq));
    btns[i].classList.toggle('current', i===current);
  });
}

function typeLabel(t){
  return {single:'SINGLE CHOICE', multi:'MULTI SELECT'}[t];
}

function render(){
  const q = Q[current];
  document.getElementById('qCounter').textContent = 'Question ' + q.q + ' / ' + TOTAL;
  document.getElementById('qTypeTag').textContent = typeLabel(q.type);
  document.getElementById('qStem').textContent = q.stem;

  const codeEl = document.getElementById('qCode');
  if(q.code){ codeEl.style.display='block'; codeEl.textContent = q.code; }
  else{ codeEl.style.display='none'; }

  const flagEl = document.getElementById('qFlag');
  if(q.flag){ flagEl.style.display='block'; flagEl.textContent = '⚠ ' + q.flag; }
  else{ flagEl.style.display='none'; }

  const body = document.getElementById('qBody');
  body.innerHTML='';

  if(q.type==='single'){
    const wrap = document.createElement('div'); wrap.className='choiceList';
    q.opts.forEach(([k,v])=>{
      const div = document.createElement('label'); div.className='choice';
      div.innerHTML = '<input type="radio" name="single'+q.q+'"><span class="txt"></span>';
      div.querySelector('.txt').textContent = v;
      const input = div.querySelector('input');
      input.checked = answers[q.q]===k;
      if(answers[q.q]===k) div.classList.add('selected');
      input.onchange = ()=>{ answers[q.q]=k; updateProgress(); render(); };
      wrap.appendChild(div);
    });
    body.appendChild(wrap);
    if(graded) applySingleFeedback(q, wrap);
  }

  if(q.type==='multi'){
    const hint = document.createElement('div'); hint.className='hint';
    hint.textContent = 'Select exactly '+q.n+' choice(s).';
    body.appendChild(hint);
    const wrap = document.createElement('div'); wrap.className='choiceList';
    if(!answers[q.q]) answers[q.q]=[];
    q.opts.forEach(([k,v])=>{
      const div = document.createElement('label'); div.className='choice';
      div.innerHTML = '<input type="checkbox"><span class="txt"></span>';
      div.querySelector('.txt').textContent = v;
      const input = div.querySelector('input');
      input.checked = answers[q.q].includes(k);
      if(input.checked) div.classList.add('selected');
      input.onchange = ()=>{
        let arr = answers[q.q];
        if(input.checked){ arr.push(k); } else { arr = arr.filter(x=>x!==k); }
        answers[q.q]=arr;
        updateProgress(); render();
      };
      wrap.appendChild(div);
    });
    body.appendChild(wrap);
    if(graded) applyMultiFeedback(q, wrap);
  }

  const fb = document.getElementById('feedbackBox');
  fb.className=''; fb.innerHTML='';
  if(graded){
    const correct = gradeResults[q.q];
    fb.className = correct ? 'ok':'bad';
    fb.textContent = correct ? '✔ Correct.' : '✘ Not quite — the correct answer is highlighted above.';
  }

  document.getElementById('prevBtn').disabled = current===0;
  document.getElementById('nextBtn').textContent = current===TOTAL-1 ? 'Finish ▸' : 'Next ▸';
  updateProgress();
}

function applySingleFeedback(q, wrap){
  const labels = wrap.querySelectorAll('.choice');
  labels.forEach((div,i)=>{
    const k = q.opts[i][0];
    div.querySelector('input').disabled = true;
    if(k===q.ans) div.classList.add('showCorrect');
    else if(answers[q.q]===k) div.classList.add('showWrong');
  });
}
function applyMultiFeedback(q, wrap){
  const labels = wrap.querySelectorAll('.choice');
  labels.forEach((div,i)=>{
    const k = q.opts[i][0];
    div.querySelector('input').disabled = true;
    const chosen = answers[q.q].includes(k);
    if(q.ans.includes(k)) div.classList.add('showCorrect');
    else if(chosen) div.classList.add('showWrong');
  });
}

document.getElementById('prevBtn').onclick = ()=>{ if(current>0){ current--; render(); } };
document.getElementById('nextBtn').onclick = ()=>{
  if(current<TOTAL-1){ current++; render(); }
  else { gradeQuiz(); }
};
document.getElementById('finishBtn').onclick = gradeQuiz;

function gradeQuestion(q){
  const a = answers[q.q];
  if(q.type==='single') return a===q.ans;
  if(q.type==='multi'){
    if(!a || a.length!==q.ans.length) return false;
    const s1=[...a].sort().join(','); const s2=[...q.ans].sort().join(',');
    return s1===s2;
  }
  return false;
}

function gradeQuiz(){
  graded = true;
  let correctCount = 0;
  Q.forEach(q=>{
    const ok = gradeQuestion(q);
    gradeResults[q.q]=ok;
    if(ok) correctCount++;
  });
  showResults(correctCount);
}

function showResults(correctCount){
  document.getElementById('quizScreen').style.display='none';
  document.getElementById('resultsScreen').style.display='block';
  document.getElementById('sidebar').style.display='none';
  const pct = Math.round(correctCount/TOTAL*100);
  document.getElementById('scoreBig').textContent = pct+'%';
  document.getElementById('scoreSub').textContent = correctCount+' of '+TOTAL+' correct';
  const grid = document.getElementById('resultsGrid');
  grid.innerHTML='';
  Q.forEach(q=>{
    const box = document.createElement('div');
    box.className = 'rBox ' + (gradeResults[q.q] ? 'correct':'incorrect');
    box.textContent = q.q;
    box.onclick = ()=>{ jumpToReview(q.q-1); };
    grid.appendChild(box);
  });
}

function jumpToReview(idx){
  document.getElementById('resultsScreen').style.display='none';
  document.getElementById('quizScreen').style.display='block';
  document.getElementById('sidebar').style.display='flex';
  current = idx;
  render();
}

document.getElementById('reviewWrongBtn').onclick = ()=>{
  const firstWrong = Q.findIndex(q=>!gradeResults[q.q]);
  jumpToReview(firstWrong===-1?0:firstWrong);
};
document.getElementById('retakeBtn').onclick = ()=>{
  answers = {}; graded=false; gradeResults={}; current=0;
  document.getElementById('resultsScreen').style.display='none';
  document.getElementById('quizScreen').style.display='block';
  document.getElementById('sidebar').style.display='flex';
  render();
};

loadQuiz(activeQuizId);
</script>
</body>
</html>