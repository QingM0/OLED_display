function sendJson(value) {
  const jsonData = { number: value };

  fetch('https://test.qingmo.moe/save', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(jsonData),
  })
  .then(response => response.json())
  .then(data => {
    console.log('保存成功:', data);
    // 替换弹窗为页面提示
    document.getElementById('savedData').innerHTML = `JSON ${value} 发送成功!`;
  })
  .catch(error => console.error('发生错误:', error));
}

function clearData() {
  fetch('https://test.qingmo.moe/clear', {
    method: 'DELETE',
  })
  .then(response => response.json())
  .then(data => {
    console.log('数据已清空:', data);
    // 替换弹窗为页面提示
    document.getElementById('savedData').innerHTML = '数据已清空!';
    document.getElementById('savedData').innerHTML = '';  // 清空显示的数据
  })
  .catch(error => console.error('发生错误:', error));
}

  // 获取保存的数据并显示在页面上
  function getSavedData() {
    fetch('https://test.qingmo.moe/data')
      .then(response => response.json())
      .then(data => {
        const savedDataDiv = document.getElementById('savedData');
        savedDataDiv.innerHTML = '<h3>已发送的数据:</h3>' + JSON.stringify(data, null, 2);
      })
      .catch(error => console.error('发生错误:', error));
  }
  